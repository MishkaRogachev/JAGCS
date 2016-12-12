import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

Frame {
    id: root

    property var coordinate: QtPositioning.coordinate()
    signal setCoordinate(var coordinate)

    ColumnLayout {
        anchors.fill: parent

        // TODO: mission item type: takeoff, waypoint, etc

        PositionEdit {
            id: position

            latitude: coordinate.latitude
            longitude: coordinate.longitude
            onLatitudeChanged: updateCoordinate()
            onLongitudeChanged: updateCoordinate()
        }

        RowLayout {
            Label {
                Layout.fillWidth: true
                text: qsTr("Alt.:")
            }

            SpinBox {
                id: altitude
                Layout.fillWidth: true
                from: -1000
                to: 20000
                value: coordinate.altitude
                onValueChanged: updateCoordinate()
            }
        }
    }

    function updateCoordinate() {
        root.setCoordinate(QtPositioning.coordinate(position.latitude,
                                                    position.longitude,
                                                    altitude.value));
    }
}
