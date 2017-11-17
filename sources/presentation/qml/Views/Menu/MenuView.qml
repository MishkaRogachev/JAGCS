import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

Controls.Pane {
    id: menu

    function home() {
        loader.source = "TopMenu.qml";
        currentLabel.text = "";
        pathModel.clear();
    }

    function deepIn(source, text) {
        loader.source = source;
        pathModel.append({ "source": source, "text": text });
        currentLabel.text = text;
    }

    function backOut(index) {
        loader.source = pathModel.get(index).source;
        currentLabel.text = pathModel.get(index).text;

        if (index + 1 < pathModel.count) {
            pathModel.remove(index + 1, pathModel.count - index - 1);
        }
    }

    padding: 0
    Component.onCompleted: home()

    ColumnLayout {
        anchors.fill: parent
        spacing: palette.spacing

        RowLayout {
            Controls.Button {
                tipText: qsTr("Home")
                iconSource: "qrc:/icons/home.svg"
                flat: true
                enabled: loader.source != "TopMenu.qml"
                onClicked: home()
            }

            Repeater {
                model: ListModel { id: pathModel }

                Controls.Button {
                    text: model.text
                    flat: true
                    visible: index + 1 < pathModel.count
                    onClicked: backOut(index)
                }
            }

            Controls.Label {
                id: currentLabel
                font.bold: true
            }
        }

        Flickable {
            id: flickable
            contentHeight: loader.height
            flickableDirection: Flickable.VerticalFlick
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: palette.margins

            Controls.ScrollBar.vertical: Controls.ScrollBar {}

            Loader {
                id: loader
                width: parent.width
                onItemChanged: {
                    if (!item) return;

                    menu.width = item.implicitWidth + palette.margins * 2
                    item.height = Qt.binding(function() {
                        return Math.max(item.implicitHeight, flickable.height);
                    } );
                }

                Connections {
                    target: loader.item
                    ignoreUnknownSignals: true
                    onReqestComponent: menu.deepIn(source, text)
                }
            }
        }
    }
}
