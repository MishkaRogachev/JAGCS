import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

RowLayout {
    id: root

    property QtObject item

    property var avalibleCommands: [
        qsTr("UNKNOWN"), qsTr("TAKEOFF"), qsTr("WAYPOINT"),
        qsTr("LOITER"), qsTr("RETURN"), qsTr("CONTINUE"),
        qsTr("LANDING") ]
    // TODO: avalibleCommands enum handling

    signal remove()

    function pick() { pickButton.pick(); }

    Label {
        Layout.preferredWidth: 24
        font.bold: true
        text: item.sequence + ")"
    }

    ComboBox {
        Layout.minimumWidth: 110
        Layout.fillWidth: true
        model: avalibleCommands
        currentIndex: item.command
        onCurrentIndexChanged: item.setCommand(currentIndex)
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
        value: item.latitude
        onValueChanged: if (!isNaN(value)) item.setLatitude(value)
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
        value: item.longitude
        onValueChanged: if (!isNaN(value)) item.setLongitude(value)
    }

    Label {
        Layout.minimumWidth: 40
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Alt.:")
    }

    SpinBox {
        Layout.minimumWidth: 160
        Layout.fillWidth: true
        from: -1000
        to: 20000
        value: item.altitude
        onValueChanged: if (!isNaN(value)) item.setAltitude(value)
    }

    CheckBox {
        text: qsTr("Relative")
        checked: item.relativeAltitude
        onCheckedChanged: item.setRelativeAltitude(checked)
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
