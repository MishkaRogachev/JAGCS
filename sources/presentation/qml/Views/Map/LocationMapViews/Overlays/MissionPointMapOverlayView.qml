import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Views/Common"

MapItemView {
    delegate: MapQuickItem {
        coordinate: itemCoordinate
        visible: itemVisible
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: itemSelected ? 999 : 500

        sourceItem: MissionItemView {
            selected: itemSelected
            current: itemPtr.current
            reached: itemPtr.reached
            status: itemPtr.status
            command: itemPtr.command
            sequence: itemPtr.sequence
            selectionAvalible: !picking
            onSelectionRequest: pointModel.setSelectedMissionItem(itemIndex)
            onHolded: pointModel.holded()
        }
    }
}

