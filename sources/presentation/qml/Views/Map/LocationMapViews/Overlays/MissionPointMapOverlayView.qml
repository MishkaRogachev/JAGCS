import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
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
            //                drawer.setMode(DrawerPresenter.Plan);
            //                map.selectItem(itemPtr.missionId, itemPtr.id);
            //                if (trackingVehicleId == 0) map.setCenterOffsetted(itemCoordinate);
            //            }
            onDragged: {
                var point = map.fromCoordinate(itemCoordinate);
                point.x += dx;
                point.y += dy;
                var coordinate = map.toCoordinate(point);
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

            Connections {
                target: map
                onHolded: {
                    if (!itemSelected) return;
                    presenter.moveItem(itemPtr.id, coordinate.latitude, coordinate.longitude);
                }
            }
        }
    }
}

