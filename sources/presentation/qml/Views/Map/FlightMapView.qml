import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapView {
    id: root

    property var vehicleModel

    MapItemView {
        id: backgroundTracks
        model: vehicleModel
        autoFitViewport: true
        delegate: MapPolyline {
            line.width: 6
            line.color: palette.backgroundColor
            path: track
            smooth: true
        }
    }

    MapItemView {
        id: tracks
        model: vehicleModel
        delegate: MapPolyline {
            line.width: 4
            line.color: palette.selectionColor
            path: track
            smooth: true
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
