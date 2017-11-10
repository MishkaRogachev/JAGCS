import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Control
import "qrc:/Views/Common"

MapItemView {
    id: root

    delegate: MapQuickItem {
        coordinate: targetPosition
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: 50

        sourceItem: MissionItemView {
            current: true
            sequence: vehicleId
            command: MissionItem.TargetPoint
        }
    }
}
