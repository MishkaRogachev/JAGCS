import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "qrc:/Views/Common"

ColumnLayout {
    id: mapSettings

    property int osmActiveMapType: -1
    property int mapBoxActiveMapType: -1
    property int esriActiveMapType: -1

    property bool changed: false

    property alias plugins: pluginBox.model
    property alias plugin: pluginBox.currentIndex
    property alias cacheSize: cacheSizeBox.value
    property alias highdpiTiles: highdpiTilesBox.checked
    property alias trackLength: trackLengthSlider.value

    spacing: industrial.spacing

    onPluginChanged: {
        if (main.mapType !== plugin) main.reloadMap(plugin);
        updateMapTypes();
    }

    onOsmActiveMapTypeChanged: if (main.mapType === 0) activeMapTypeBox.currentIndex = osmActiveMapType
    onMapBoxActiveMapTypeChanged: if (main.mapType === 1) activeMapTypeBox.currentIndex = mapBoxActiveMapType
    onEsriActiveMapTypeChanged: if (main.mapType === 2) activeMapTypeBox.currentIndex = esriActiveMapType
    Component.onDestruction: if (changed) presenter.updateView()

    MapSettingsPresenter {
        id: presenter
        view: mapSettings
        Component.onCompleted: updateView()
    }

    Connections {
        target: main
        onMapChanged: updateMapTypes()
    }

    function updateMapTypes() {
        var types = new Array(0);
        if (map) {
            for (var i = 0; i < map.supportedMapTypes.length; ++i) {
                var array = map.supportedMapTypes[i].name.split("/");
                types.push(array[array.length - 1]);
            }
        }
        activeMapTypeBox.model = types;
        activeMapTypeBox.currentIndex = map.activeMapTypeIndex;
    }

    RowLayout {
        spacing: industrial.spacing

        Controls.ComboBox {
            id: pluginBox
            labelText: qsTr("Map provider")
            currentIndex: -1
            onActivated: changed = true
            Layout.fillWidth: true
        }

        SaveRestore {
            enabled: changed
            onSave: presenter.save()
            onRestore: presenter.updateView()
        }
    }

    Controls.ComboBox {
        id: activeMapTypeBox
        labelText: qsTr("Map type")
        onCurrentIndexChanged: {
            switch (plugin) {
            case 0:
                osmActiveMapType = currentIndex;
                break;
            case 1:
                mapBoxActiveMapType = currentIndex;
                break;
            case 2:
                esriActiveMapType = currentIndex;
                break;
            default:
                return;
            }

            map.activeMapTypeIndex = currentIndex;

            changed = true;
        }
        Layout.fillWidth: true
    }

    Controls.SpinBox {
        id: cacheSizeBox
        labelText: qsTr("Cache size")
        Layout.fillWidth: true
        onValueChanged: changed = true
        to: 2147483647 // TODO: to helper
    }

    Controls.CheckBox {
        text: qsTr("High DPI tiles")
        id: highdpiTilesBox
        onCheckedChanged: changed = true
    }

    Controls.Label {
        horizontalAlignment: Text.AlignHCenter
        text: qsTr("Track length") + ": " + (trackLengthSlider.visualValue > -1 ?
                                     trackLengthSlider.visualValue.toFixed(0) : qsTr("Infinite"))
        Layout.fillWidth: true
    }

    Controls.Slider {
        id: trackLengthSlider
        from: -1
        to: 1000
        onPressedChanged: if (!pressed) changed = true
        Layout.fillWidth: true
    }

    Item { Layout.fillHeight: true }
}
