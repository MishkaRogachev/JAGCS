import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapView {
    id: root

    property var vehicleModel

    MapItemView {
        id: backgroundTracks
        model: vehicleModel
        delegate: MapPolyline {
            line.width: 6
            line.color: palette.backgroundColor
            path: track
            smooth: true
            opacity: 0.8
        }
    }

    MapItemView {
        id: tracks
        model: vehicleModel
        delegate: MapPolyline {
            line.width: 2
            line.color: palette.selectionColor
            path: track
            smooth: true
            opacity: 0.8
        }
    }

    MapItemView {
        id: vehicles
        model: vehicleModel
        autoFitViewport: true
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
