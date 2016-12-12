import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

Map {
    id: root

    signal picked(real latitude, real longitude)

    plugin: Plugin { name: "osm" }
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    activeMapType: supportedMapTypes[5] // TerrainMapType
    copyrightsVisible: false

    MouseArea {
        anchors.fill: parent

        onClicked: {
            var point = map.toCoordinate(Qt.point(mouseX, mouseY), true);
            map.picked(point.latitude, point.longitude);
        }
    }
}
