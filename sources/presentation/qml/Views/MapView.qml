import QtQuick 2.6
import QtLocation 5.5
import QtPositioning 5.5

Map {
    plugin: Plugin { name: "osm" }
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    activeMapType: supportedMapTypes[5] // TerrainMapType

    MouseArea { // FIXME: touch gestures bug workaround, must be fixed since Qt 5.6
        anchors.fill: parent
    }
}
