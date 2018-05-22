import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Views/Common"

MapItemView {
    delegate: MapQuickItem {
        property bool itemSelected: itemPtr.id === selectedItemId
        coordinate: itemCoordinate
        visible: itemVisible
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: itemSelected ? 999 : 500

        sourceItem: PointView {
            selected: itemSelected
            current: itemCurrent
            reached: itemPtr.reached
            status: itemPtr.status
            command: itemPtr.command
            sequence: itemPtr.sequence
            mouseEnabled: !picking
            onClicked: map.selectItem(itemPtr.missionId, itemPtr.id)
            onHolded: {
                menu.setMode(DrawerPresenter.Planning);
                map.selectItem(itemPtr.missionId, itemPtr.id)
            }
        }
    }
}

