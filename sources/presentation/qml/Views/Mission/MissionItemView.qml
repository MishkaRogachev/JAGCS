import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

Frame {
    id: root

    property var coordinate: QtPositioning.coordinate()
    property bool updating: false
    signal setCoordinate(var coordinate)
    signal remove()

    ColumnLayout {
        anchors.fill: parent

        // TODO: mission item type: takeoff, waypoint, etc

        PositionEdit {
            id: position
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
                onValueChanged: updateCoordinate()
            }
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Remove")
            onClicked: root.remove()
        }
    }

    onCoordinateChanged: {
        updating = true;
        position.latitude = coordinate.latitude;
        position.longitude = coordinate.longitude;
        altitude.value = coordinate.altitude;
        updating = false;
    }

    function updateCoordinate() {
        if (updating) return;
        root.setCoordinate(QtPositioning.coordinate(position.latitude,
                                                    position.longitude,
                                                    altitude.value));
    }
}
