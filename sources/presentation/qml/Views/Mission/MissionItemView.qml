import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

RowLayout {
    id: root

    property int seq: -1
    property var coordinate: QtPositioning.coordinate()

    signal remove()

    function pick() { pickButton.checked = true; }

    Label {
        Layout.preferredWidth: 24
        font.bold: true
        text: seq + ")"
    }

    ComboBox {
        Layout.preferredWidth: 110
        model: [ "WAYPOINT", "TAKEOFF" ] // TODO: mission types
    }

    Label {
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Lat.:")
    }

    CoordSpinBox {
        Layout.preferredWidth: 230
        value: coordinate.latitude
        onValueChanged: coordinate.latitude = value;
    }

    Label {
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Lon.:")
    }

    CoordSpinBox {
        Layout.preferredWidth: 230
        isLongitude: true
        value: coordinate.longitude
        onValueChanged: coordinate.longitude = value;
    }

    Label {
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Alt.:")
    }

    SpinBox {
        id: altitude
        Layout.preferredWidth: 160
        from: -1000
        to: 20000
        value: coordinate.altitude
        onValueChanged: coordinate.altitude = value;
    }

    Button {
        id: pickButton // TODO: mapButton control
        anchors.verticalCenter: parent.verticalCenter
        iconSource: "qrc:/icons/map-marker.svg"
        checkable: true
        // TODO: ask map stop/start picking

        Connections {
            target: map
            onPicked: {
                if (!pickButton.checked) return;
                coordinate.latitude = latitude;
                coordinate.longitude = longitude;
                pickButton.checked = false;
            }
        }
    }

    Button {
        iconSource: "qrc:/icons/remove.svg"
        iconColor: palette.negativeColor
        onClicked: root.remove()
    }
}
