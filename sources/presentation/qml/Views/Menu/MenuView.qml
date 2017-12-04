import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

ColumnLayout {
    id: menu

    property string homeSource: "TopMenu.qml"
    readonly property bool atHome: pathModel.count == 0

    function home() {
        loader.setSource(homeSource);
        topbar.currentContext = "";
        pathModel.clear();
    }

    function deepIn(source, text, properties) {
        loader.setSource(source, properties);
        pathModel.append({ "source": source, "text": text });
        topbar.currentContext = text;
        return loader.item;
    }

    function backOut(index) {
        loader.source = pathModel.get(index).source;
        topbar.currentContext = pathModel.get(index).text;

        if (index + 1 < pathModel.count) {
            pathModel.remove(index + 1, pathModel.count - index - 1);
        }
    }

    spacing: sizings.spacing
    Component.onCompleted: home()

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
