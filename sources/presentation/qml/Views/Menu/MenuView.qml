import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

ColumnLayout {
    id: menu

    property string contextText
    property string homeSource: "TopMenu.qml"
    readonly property bool atHome: contextModel.count == 0

    function home() {
        loader.setSource(homeSource);
        contextText = "";
        contextModel.clear();
    }

    function deepIn(source, text, properties) {
        loader.setSource(source, properties);
        contextModel.append({ "source": source, "text": text });
        contextText = text;
        return loader.item;
    }

    function backOut(index) {
        loader.source = contextModel.get(index).source;
        contextText = contextModel.get(index).text;

        if (index + 1 < contextModel.count) {
            contextModel.remove(index + 1, contextModel.count - index - 1);
        }
    }

    spacing: sizings.spacing
    Component.onCompleted: home()

    ListModel { id: contextModel }

    RowLayout {
        spacing: sizings.spacing

        Controls.Button {
            tipText: qsTr("Home")
            iconSource: "qrc:/icons/home.svg"
            flat: true
            enabled: !atHome
            onClicked: home()
        }

        Repeater {
            model: contextModel

            Controls.Button {
                text: model.text
                flat: true
                visible: index + 1 < contextModel.count
                onClicked: backOut(index)
            }
        }

        Controls.Label {
            text: contextText
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Flickable {
        id: flickable
        contentHeight: loader.height
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: sizings.margins

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        // TODO: heal loader to use qml components instead raw sources
        Loader {
            id: loader
            width: parent.width
            onItemChanged: {
                if (!item) return;

                menu.width = Qt.binding(function() {
                    return item.implicitWidth + sizings.margins * 2
                });
                item.height = Qt.binding(function() {
                    return Math.max(item.implicitHeight, flickable.height);
                });
            }

            Connections {
                target: loader.item
                ignoreUnknownSignals: true
                onReqestComponent: menu.deepIn(source, text, properties)
            }
        }
    }
}
