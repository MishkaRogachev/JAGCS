import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"

RowLayout {
    id: root

    property int seq: -1
    property var coordinate: QtPositioning.coordinate()
    property alias command: commandBox.currentIndex
    property var avalibleCommands: [ qsTr("UNKNOWN"), qsTr("TAKEOFF"),
        qsTr("WAYPOINT"), qsTr("LOITER"), qsTr("RETURN"), qsTr("LANDING") ]
    // TODO: avalibleCommands enum handling

    signal remove()

    function pick() { pickButton.pick(); }

    Label {
        Layout.preferredWidth: 24
        font.bold: true
        text: seq + ")"
    }

    ComboBox {
        id: commandBox
        Layout.minimumWidth: 110
        Layout.fillWidth: true
        model: avalibleCommands
    }

    Label {
        Layout.minimumWidth: 40
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Lat.:")
    }

    CoordSpinBox {
        id: latitudeSpinBox
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
        id: longitudeSpinBox
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
        onPicked: {
            latitudeSpinBox.value = coordinate.latitude;
            longitudeSpinBox.value = coordinate.longitude;
        }
    }

    Button {
        iconSource: "qrc:/icons/remove.svg"
        iconColor: palette.negativeColor
        onClicked: root.remove()
    }
}
