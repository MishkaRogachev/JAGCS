import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

RowLayout {
    id: root

    property int seq: -1
    property alias latitude: latitudeSpinBox.value
    property alias longitude: longitudeSpinBox.value
    property alias altitude: altitudeSpinBox.value
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
    }

    Label {
        Layout.minimumWidth: 40
        horizontalAlignment: Text.AlignRight
        Layout.fillWidth: true
        text: qsTr("Alt.:")
    }

    SpinBox {
        id: altitudeSpinBox
        Layout.minimumWidth: 160
        Layout.fillWidth: true
        warning: isNaN(altitude)
        from: -1000
        to: 20000
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
