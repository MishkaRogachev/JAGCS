import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
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

    RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right

        Label {
            font.bold: true
            text: qsTr("#") + item.sequence
        }

        ComboBox {
            model: avalibleCommands
            currentIndex: item.command
            onCurrentIndexChanged: item.setCommand(currentIndex)
        }

        GridLayout {
            id: coordinateColumn
            visible: item.hasPosition
            columns: 2

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Lat.:")
            }

            CoordSpinBox {
                Layout.fillWidth: true
                id: latitudeSpinBox
                value: item.latitude
                onValueChanged: if (!isNaN(value)) item.setLatitude(value)
            }

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Lon.:")
            }

            CoordSpinBox {
                Layout.fillWidth: true
                id: longitudeSpinBox
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

        GridLayout {
            visible: item.command !== 6 // TODO: command enum
            columns: 2

            Label {
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                text: qsTr("Alt.:")
            }

            SpinBox {
                Layout.fillWidth: true
                from: -1000
                to: 20000
                value: item.altitude
                onValueChanged: if (!isNaN(value)) item.setAltitude(value)
            }

            Item { width: 1; height: 1 }

            CheckBox {
                Layout.fillWidth: true
                text: qsTr("Relative alt.")
                checked: item.relativeAltitude
                onCheckedChanged: item.setRelativeAltitude(checked)
            }
        }

        GridLayout {
            columns: 2

            Label {
                Layout.fillWidth: true
                visible: pitch.visible
                horizontalAlignment: Text.AlignRight
                text: qsTr("Pitch:")
            }

            SpinBox {
                id: pitch
                Layout.fillWidth: true
                visible: item.command === 2 // TODO: command enum
                from: 0
                to: 360
                value: item.pitch
                onValueChanged: if (!isNaN(value)) item.setPitch(value)
            }

            Label {
                Layout.fillWidth: true
                visible: yaw.visible
                horizontalAlignment: Text.AlignRight
                text: qsTr("Yaw:")
            }

            SpinBox {
                id: yaw
                Layout.fillWidth: true
                visible: item.command === 2 || item.command === 7 // TODO: command enum
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
}
