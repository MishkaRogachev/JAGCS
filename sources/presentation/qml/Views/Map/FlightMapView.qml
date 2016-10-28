import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapView {
    id: root

    property var vehicles // TODO: QAbstractItemModel

    MapItemView {
        model: vehicles
        delegate: MapQuickItem {
            anchorPoint.x: markItem.width / 2
            anchorPoint.y: markItem.height / 2
            coordinate: position

            sourceItem: Item {
                id: markItem
                width: 64
                height: 64

                Image {
                    anchors.centerIn: parent
                    rotation: direction
                    source: mark
                }
            }
        }
    }
}
