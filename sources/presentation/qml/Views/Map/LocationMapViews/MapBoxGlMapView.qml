import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

BaseMapView {
    id: map

    plugin: Plugin {
        name: "mapboxgl"

        PluginParameter { name: "mapboxgl.mapping.cache.size"; value: settings.value("Map/cacheSize") }
        PluginParameter { name: "mapboxgl.mapping.use_fbo"; value: false }
    }

    activeMapTypeIndex: settings.value("Map/mapBoxActiveMapType")
}
