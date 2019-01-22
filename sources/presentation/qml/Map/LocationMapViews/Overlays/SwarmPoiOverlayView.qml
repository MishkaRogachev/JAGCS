import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "qrc:/Views/Common"
import "../../MapItems"

MapItemView {
    // FIXME: merge with mission point
//    roles[SwarmPoiCoordinateRole] = "swarmPoiPosition";
//    roles[SwarmPoiGroupRole] = "swarmPoiGroup";
//    roles[SwarmPoiNumberRole] = "swarmPoiNumber";
    delegate: MapQuickItem {
        id: mapItem
        coordinate: swarmPoiPosition
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: 50

        sourceItem: Item {
            width: controlSize.baseSize
            height: controlSize.baseSize

            Rectangle {
                anchors.fill: parent
                rotation: 45
                color: customPalette.activeMissionColor
                border.width: 2
                border.color: customPalette.backgroundColor
            }

            Controls.Label {
                anchors.right: parent.right
                anchors.top: parent.top
                text: swarmPoiNumber
                color: customPalette.textColor
                font.pixelSize: controlSize.fontSize * 0.5
            }

            Controls.Label {
                anchors.right: parent.right
                anchors.top: parent.top
                text: vehicleId
                color: customPalette.activeMissionColor
                font.pixelSize: controlSize.fontSize * 0.33
            }

            Controls.Label {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                text: swarmPoiGroup
                color: customPalette.activeMissionColor
                font.pixelSize: controlSize.fontSize * 0.33
            }

//            onDragged: {
//                var point = map.fromCoordinate(targetPosition, false);
//                point.x += dx;
//                point.y += dy;

//                if (point.x < 0) map.pan(point.x, 0);
//                else if (point.x > map.width) map.pan(point.x - map.width, 0);
//                if (point.y < 0) map.pan(0, point.y);
//                else if (point.y > map.height) map.pan(0, point.y - map.height);
//            }
//            onDropped: {
//                var point = map.fromCoordinate(targetPosition);
//                point.x += dx;
//                point.y += dy;
//                var coordinate = map.toCoordinate(point);
//                if (!coordinate.isValid) return;

//                presenter.navTo(vehicleId, coordinate.latitude, coordinate.longitude,
//                                targetPosition.altitude - homePosition.altitude);
//            }
//            onHolded: popup.open()

//            Controls.Popup {
//                id: popup
//                y: pointView.height
//                closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

//                SetPoint {
//                    title: qsTr("Nav to") + " " + vehicleName
//                    onVisibleChanged: {
//                        if (!visible) return;

//                        latitude = targetPosition.latitude;
//                        longitude = targetPosition.longitude;
//                        altitude = targetPosition.altitude - homePosition.altitude;
//                    }
//                    onSetPoint: presenter.navTo(vehicleId, latitude, longitude, altitude);
//                }
//            }
        }
    }
}
