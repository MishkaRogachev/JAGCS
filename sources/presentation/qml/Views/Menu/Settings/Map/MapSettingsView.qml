import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../../../Map/LocationMapViews"

GridLayout {
    id: root
    columns: 2
    rowSpacing: palette.spacing
    columnSpacing: palette.spacing

    property int osmActiveMapType: -1
    property int mapBoxGlActiveMapType: -1
    property int esriActiveMapType: -1

    property bool changed: false

    property alias plugin: pluginBox.currentIndex
    property alias cacheSize: cacheSizeBox.value
    property alias highdpiTiles: highdpiTilesBox.checked
    property alias trackLength: trackLengthSlider.value

    signal save()
    signal restore()

    Component.onCompleted: updateMapTypes()
    onChangedChanged: if (!changed) main.reloadMap()

    Connections {
        target: main
        onMapChanged: updateMapTypes()
    }

    function updateMapTypes() {
        var types = new Array(0);
        if (map) {
            for (var i = 0; i < map.supportedMapTypes.length; ++i) {
                types.push(map.supportedMapTypes[i].name);
            }
        }
        activeMapTypeBox.model = types;
    }

    Controls.Label {
        text: qsTr("Map provider")
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        id: pluginBox
        model: [ "OSM", "Map Box", "Esri" ]
        currentIndex: -1
        onCurrentIndexChanged: changed = true
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Map type")
        Layout.fillWidth: true
    }

    Controls.ComboBox {
        id: activeMapTypeBox
        onActivated: {
            switch (plugin) {
            case 0:
                osmActiveMapType = currentIndex;
                break;
            case 1:
                mapBoxGlActiveMapType = currentIndex;
                break;
            case 2:
                esriActiveMapType = currentIndex;
                break;
            default:
                return;
            }

            changed = true;
        }
        Layout.fillWidth: true
    }

    Controls.Label {
        text: qsTr("Cache size")
        Layout.fillWidth: true
    }

    Controls.SpinBox {
        id: cacheSizeBox
        Layout.fillWidth: true
        onValueChanged: changed = true
        to: 2147483647 // TODO: to helper
    }

    Controls.Label {
        text: qsTr("High DPI tiles")
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: highdpiTilesBox
        onCheckedChanged: changed = true
    }

    Controls.Label {
        text: qsTr("Track length")
        Layout.fillWidth: true
    }

    RowLayout {
        spacing: palette.spacing

        Controls.Slider {
            id: trackLengthSlider
            from: -1
            to: 1000
            Layout.fillWidth: true
            onPressedChanged: if (!pressed) changed = true
        }

        Controls.Label {
            Layout.preferredWidth: 86
            horizontalAlignment: Text.AlignHCenter
            text: trackLengthSlider.visualValue > -1 ?
                      trackLengthSlider.visualValue.toFixed(0) : qsTr("Infinite")
        }
    }

    Item {
        Layout.fillHeight: true
    }

    RowLayout {
        spacing: palette.spacing
        Layout.columnSpan: 2

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
            onClicked: save()
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
