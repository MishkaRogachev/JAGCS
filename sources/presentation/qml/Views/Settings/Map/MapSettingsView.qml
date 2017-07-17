import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../../Map"

Controls.Frame {
    id: root

    property bool changed: false

    property alias cacheFolder: cacheField.text
    property alias cacheSize: cacheSizeBox.value
    property alias tileHost: tileHostField.text
    property alias activeMapType: mapTypeBox.currentIndex

    signal save()
    signal restore()

    GridLayout {
        anchors.fill: parent
        rowSpacing: palette.spacing
        columns: 2

        Controls.Label {
            text: qsTr("Map provider")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            enabled: false
            model: [ "QtLocation" ] // TODO: map providers
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Map type")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: mapTypeBox
            model: []
            onCurrentIndexChanged: changed = true
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Tile host")
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: tileHostField
            placeholderText: qsTr("Enter tile host url")
            Layout.fillWidth: true
            onTextChanged: changed = true
            enabled: mapTypeBox.currentIndex === mapTypeBox.model.length - 1
        }

        Controls.Label {
            text: qsTr("Cache folder")
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: cacheField
            placeholderText: qsTr("Enter map cache folder")
            Layout.fillWidth: true
            onTextChanged: changed = true
        }

        Controls.Label {
            text: qsTr("Cache size")
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: cacheSizeBox
            Layout.fillWidth: true
            onValueChanged: changed = true;
            to: 2147483647 // TODO: to helper
        }

        Component {
            id: mapComponent

            MapView {
                id: map
                Component.onCompleted: {
                    var types = new Array(0);
                    for (var i = 0; i < supportedMapTypes.length; ++i) {
                        types.push(supportedMapTypes[i].name);
                    }
                    mapTypeBox.model = types;
                }
            }
        }

        Loader {
            id: mapPreview
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.columnSpan: 2
            Component.onCompleted: reload()
            function reload() {
                sourceComponent = null;
                sourceComponent = mapComponent;
            }
        }

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: {
                save();
                mapPreview.reload();
            }
            enabled: changed
            Layout.fillWidth: true
        }
    }
}

