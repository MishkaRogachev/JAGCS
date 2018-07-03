import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

BaseMapView {
    id: map

    plugin: Plugin {
        name: "esri"

        PluginParameter { name: "esri.mapping.cache.disk.size"; value: settings.value("Map/cacheSize") }
    }

    activeMapTypeIndex: settings.value("Map/esriActiveMapType")
}
