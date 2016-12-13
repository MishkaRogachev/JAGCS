import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

Frame {
    id: root

    property var coordinate: QtPositioning.coordinate()
    signal remove()

    RowLayout {
        anchors.fill: parent

        // TODO: mission item type: takeoff, waypoint, etc

        PositionEdit {
            id: position
            latitude: coordinate.latitude
            longitude: coordinate.longitude
            onLatitudeChanged: coordinate.latitude = latitude;
            onLongitudeChanged: coordinate.longitude = longitude;
        }

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
            onValueChanged: coordinate.altitude = value;
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Remove")
            onClicked: root.remove()
        }
    }
}
