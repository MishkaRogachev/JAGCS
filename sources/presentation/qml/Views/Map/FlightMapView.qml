import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapView {
    id: root

    property alias vehicleModel: vehicles.model

    MapItemView {
        id: vehicles
        delegate: MapQuickItem {
            anchorPoint.x: markItem.width / 2
            anchorPoint.y: markItem.height / 2
            coordinate: position

            sourceItem: Item {
                id: markItem
                width: markImage.sourceSize.width
                height: markImage.sourceSize.height

                Image {
                    id: markImage
                    anchors.centerIn: parent
                    rotation: direction
                    source: mark
                }
            }
        }
    }
}
