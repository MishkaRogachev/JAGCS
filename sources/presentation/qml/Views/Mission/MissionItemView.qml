import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

RowLayout {
    id: root

    property QtObject item

    property var avalibleCommands: [
        qsTr("UNKNOWN"), qsTr("HOME"), qsTr("TAKEOFF"),
        qsTr("WAYPOINT"), qsTr("LOITER"), qsTr("CONTINUE"),
        qsTr("RETURN"), qsTr("LANDING") ]
    // TODO: avalibleCommands enum handling

    signal remove()

    function pick() {
        if (pickButton.visible) pickButton.pick();
    }

    ColumnLayout {

        Label {
            Layout.preferredWidth: 24
            font.bold: true
            text: qsTr("Item #") + item.sequence
        }

        ComboBox {
            Layout.minimumWidth: 110
            Layout.preferredWidth: 160
            model: avalibleCommands
            currentIndex: item.command
            onCurrentIndexChanged: item.setCommand(currentIndex)
        }
    }

    GridLayout {
        id: coordinateColumn
        visible: item.command !== 4 && item.command !== 5 // TODO: command enum
        columns: 2

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
    }

    MapPickButton {
        id: pickButton
        visible: coordinateColumn.visible
        anchors.verticalCenter: parent.verticalCenter
        onPicked: {
            latitudeSpinBox.value = coordinate.latitude;
            longitudeSpinBox.value = coordinate.longitude;
        }
    }

    ColumnLayout {
        visible: item.command !== 5 // TODO: command enum

        RowLayout {
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
        }

        CheckBox {
            text: qsTr("Relative alt.")
            Layout.alignment: Qt.AlignHCenter
            checked: item.relativeAltitude
            onCheckedChanged: item.setRelativeAltitude(checked)
        }
    }

    GridLayout {
        columns: 2

        Label {
            visible: pitch.visible
            Layout.minimumWidth: 40
            horizontalAlignment: Text.AlignRight
            Layout.fillWidth: true
            text: qsTr("Pitch:")
        }

        SpinBox {
            id: pitch
            visible: item.command === 1 // TODO: command enum
            Layout.minimumWidth: 140
            Layout.fillWidth: true
            from: 0
            to: 360
            value: item.pitch
            onValueChanged: if (!isNaN(value)) item.setPitch(value)
        }

        Label {
            visible: yaw.visible
            Layout.minimumWidth: 40
            horizontalAlignment: Text.AlignRight
            Layout.fillWidth: true
            text: qsTr("Yaw:")
        }

        SpinBox {
            id: yaw
            visible: item.command === 1 || item.command === 6 // TODO: command enum
            Layout.minimumWidth: 140
            Layout.fillWidth: true
            from: 0
            to: 360
            value: item.yaw
            onValueChanged: if (!isNaN(value)) item.setYaw(value)
        }
    }

    Button {
        iconSource: "qrc:/icons/remove.svg"
        iconColor: palette.negativeColor
        onClicked: root.remove()
    }
}
