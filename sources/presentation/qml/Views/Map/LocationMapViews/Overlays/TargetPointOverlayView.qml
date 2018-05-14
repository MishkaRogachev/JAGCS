import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Control
import "qrc:/Views/Common"

MapItemView {
    delegate: MapQuickItem {
        id: mapItem
        coordinate: targetPosition
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: 50

        sourceItem: PointView {
            height: width
            current: true
            sequence: vehicleId
            dragEnabled: true
            command: MissionItem.TargetPoint
            onDragged: {
                var point = map.fromCoordinate(targetPosition);
                point.x += dx;
                point.y += dy;
                var coordinate = map.toCoordinate(point);
                presenter.navTo(vehicleId, coordinate.latitude, coordinate.longitude,
                                targetPosition.altitude);
            }
        }
    }
}
