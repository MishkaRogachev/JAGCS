import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapView {

    property alias vehicles: vehicleRepeater.model

    Repeater {
        id: vehicleRepeater

        MapQuickItem {
            id: boardMarker
            anchorPoint.x: mark.width / 2
            anchorPoint.y: mark.height / 2
            coordinate: modelData.navigation.position
            sourceItem: Item {
                id: mark
                width: 64
                height: 64

                Image {
                    anchors.centerIn: parent
                    rotation: modelData.attitude.yaw
                    source: "qrc:/indicators/plane_map_mark.svg"
                }
            }
        }
    }
}
