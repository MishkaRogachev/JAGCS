import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool changed: false

    property var axes: [ qsTr("No Axis"), qsTr("Axis left X"),  qsTr("Axis left Y"),
        qsTr("Axis right X"), qsTr("Axis right Y") ]

    property alias joystickEnabled: joystickEnabledBox.checked
    // property alias softwareJoystick: softwareJoystickBox.checked

    property alias pitchAxis: pitchAxisBox.currentIndex
    property alias rollAxis: rollAxisBox.currentIndex
    property alias yawAxis: yawAxisBox.currentIndex
    property alias throttleAxis: throttleAxisBox.currentIndex

    signal save()
    signal restore()

    GridLayout {
        anchors.fill: parent
        rowSpacing: palette.spacing
        columns: 2

        Controls.Label {
            text: qsTr("Joystick enabled")
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: joystickEnabledBox
            onCheckedChanged: changed = true
        }

//        Controls.Label { TODO: software joystick
//            text: qsTr("Software joystick")
//            Layout.fillWidth: true
//        }

//        Controls.CheckBox {
//            id: softwareJoystickBox
//            onCheckedChanged: changed = true
//        }

        Controls.Label {
            text: qsTr("Pitch axis")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: pitchAxisBox
            model: axes
            onCurrentIndexChanged: changed = true
            enabled: joystickEnabled
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Roll axis")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: rollAxisBox
            model: axes
            onCurrentIndexChanged: changed = true
            enabled: joystickEnabled
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Yaw axis")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: yawAxisBox
            model: axes
            onCurrentIndexChanged: changed = true
            enabled: joystickEnabled
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Throttle axis")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: throttleAxisBox
            model: axes
            onCurrentIndexChanged: changed = true
            enabled: joystickEnabled
            Layout.fillWidth: true
        }

        Item {
            Layout.columnSpan: 2
            Layout.fillHeight: true
        }

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: save()
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
