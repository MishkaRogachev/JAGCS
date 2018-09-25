import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "qrc:/Views/Common"
import "../../MapItems"

MapItemView {
    delegate: MapQuickItem {
        property bool itemSelected: itemPtr.id === selectedItemId
        coordinate: itemCoordinate
        visible: itemVisible
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: itemSelected ? 999 : 500

        sourceItem: WaypointItem {
            selected: itemSelected
            dragEnabled: itemSelected
            current: itemCurrent
            reached: itemPtr.reached
            status: itemPtr.status
            command: itemPtr.command
            sequence: itemPtr.sequence
            onClicked: map.selectItem(itemPtr.missionId, itemPtr.id)
            onHolded: menu.open()
            onDragged: {
                var point = map.fromCoordinate(itemCoordinate, false);
                point.x += dx;
                point.y += dy;

                if (point.x < 0) map.pan(point.x, 0);
                else if (point.x > map.width) map.pan(point.x - map.width, 0);
                if (point.y < 0) map.pan(0, point.y);
                else if (point.y > map.height) map.pan(0, point.y - map.height);
            }
            onDropped: {
                var point = map.fromCoordinate(itemCoordinate, false);
                point.x += dx;
                point.y += dy;
                var coordinate = map.toCoordinate(point, false);

                presenter.moveItem(itemPtr.id, coordinate.latitude, coordinate.longitude);
            }

            Controls.Menu {// TODO: round menu
                id: menu

                Controls.MenuItem {
                    iconSource: "qrc:/icons/aim.svg"
                    text: qsTr("Go to")
                    enabled: dashboard.selectedVehicle !== undefined
                    onTriggered: goTo(itemPtr.sequence)
                }

                Controls.MenuItem {
                    iconSource: "qrc:/icons/edit.svg"
                    text: qsTr("Edit point")
                    onTriggered: {
                        drawer.setMode(DrawerPresenter.Plan);
                        map.selectItem(itemPtr.missionId, itemPtr.id);
                        if (trackingVehicleId == 0) map.setCenterOffsetted(itemCoordinate);
                    }
                }
            }
        }
    }
}

