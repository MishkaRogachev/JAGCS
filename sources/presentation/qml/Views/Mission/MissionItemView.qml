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
        Layout.minimumWidth: 110
        Layout.fillWidth: true
        model: [ "WAYPOINT", "TAKEOFF" ] // TODO: mission types
    }

    Label {
        Layout.minimumWidth: 40
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Lat.:")
    }

    CoordSpinBox {
        Layout.minimumWidth: 230
        Layout.fillWidth: true
        value: coordinate.latitude
        onValueChanged: coordinate.latitude = value;
    }

    Label {
        Layout.minimumWidth: 40
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Lon.:")
    }

    CoordSpinBox {
        Layout.minimumWidth: 230
        Layout.fillWidth: true
        isLongitude: true
        value: coordinate.longitude
        onValueChanged: coordinate.longitude = value;
    }

    Label {
        Layout.minimumWidth: 40
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Alt.:")
    }

    SpinBox {
        id: altitude
        Layout.minimumWidth: 160
        Layout.fillWidth: true
        from: -1000
        to: 20000
        value: coordinate.altitude
        onValueChanged: coordinate.altitude = value;
    }

    MapPickButton {
        id: pickButton
        anchors.verticalCenter: parent.verticalCenter
        //onPicked:
    }

    Button {
        iconSource: "qrc:/icons/remove.svg"
        iconColor: palette.negativeColor
        onClicked: root.remove()
    }
}
