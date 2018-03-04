import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

GridLayout {
    id: joystickSettings

    property bool changed: false

    property var axes: [ qsTr("No Axis"), qsTr("Axis left X"),  qsTr("Axis left Y"),
        qsTr("Axis right X"), qsTr("Axis right Y") ]

    property alias joystickEnabled: joystickEnabledBox.checked
    property alias device: deviceBox.value

    property alias pitchAxis: pitch.axis
    property alias rollAxis: roll.axis
    property alias yawAxis: yaw.axis
    property alias throttleAxis: throttle.axis

    property alias pitchFactor: pitch.factor
    property alias rollFactor: roll.factor
    property alias yawFactor: yaw.factor
    property alias throttleFactor: throttle.factor

    signal save()
    signal restore()

    columns: 2
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    JoystickSettingsPresenter {
        id: presenter
        view: joystickSettings
        Component.onCompleted: updateView()
    }

    Controls.Label {
        text: qsTr("Enabled")
        Layout.fillWidth: true
    }

    Controls.CheckBox {
        id: joystickEnabledBox
        onCheckedChanged: {
            manual.setJoystickEnabled(checked);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Device")
        Layout.fillWidth: true
    }

    Controls.SpinBox {
        id: deviceBox
        enabled: joystickEnabled
        onValueChanged: {
            manual.setJoystickDevice(value)
            changed = true;
        }
        Layout.fillWidth: true
    }

    JoystickAxisView {
        id: pitch
        source: qsTr("Pitch")
        enabled: joystickEnabled
        onAxisChanged: changed = true
        onFactorChanged: changed = true
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    JoystickAxisView {
        id: roll
        source: qsTr("Roll")
        enabled: joystickEnabled
        onAxisChanged: changed = true
        onFactorChanged: changed = true
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    JoystickAxisView {
        id: throttle
        source: qsTr("Throttle")
        enabled: joystickEnabled
        onAxisChanged: changed = true
        onFactorChanged: changed = true
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    JoystickAxisView {
        id: yaw
        source: qsTr("Yaw")
        enabled: joystickEnabled
        onAxisChanged: changed = true
        onFactorChanged: changed = true
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    Item {
        Layout.columnSpan: 2
        Layout.fillHeight: true
    }

    RowLayout {
        Layout.columnSpan: 2
        spacing: sizings.spacing

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: presenter.updateView()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: presenter.save()
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
