import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

BaseMapView {
    id: map

    plugin: Plugin {
        name: "mapbox"

        // NOTE: acces token for mishkarogachev@gmail.com
        PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoibWlzaGthcm9nYWNoZXYiLCJhIjoiY2plNXJiOHJxMnp1bDJxbzZlb2cycWI3ZSJ9.twYj-is_D_fZoIl2JceIBg" }
        PluginParameter { name: "mapbox.mapping.cache.disk.size"; value: settings.value("Map/cacheSize") }
        PluginParameter { name: "mapbox.mapping.highdpi_tiles"; value: settings.boolValue("Map/highdpiTiles") }
    }

    activeMapTypeIndex: settings.value("Map/mapBoxActiveMapType")
}
