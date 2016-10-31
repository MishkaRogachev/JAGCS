import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapView {
    id: root

    property var vehicleModel

    MapItemView {
        id: tracks
        model: vehicleModel
        delegate: MapPolyline {
            line.width: 3
            line.color: palette.selectionColor
            path: track
        }
    }

    MapItemView {
        id: vehicles
        model: vehicleModel
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
