import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

GridLayout {
    id: root

    property bool updating: false

    enabled: vehicle
    columns: 2

    Label {
        text: qsTr("Pitch")
    }

    SpinBox {
        id: pitchBox
        Layout.fillWidth: true
        onValueChanged: sendPitchRollYawThottle()
    }

    Label {
        text: qsTr("Roll")
    }

    SpinBox {
        id: rollBox
        Layout.fillWidth: true
        onValueChanged: sendPitchRollYawThottle()
    }

    Label {
        text: qsTr("Yaw")
    }

    SpinBox {
        id: yawBox
        Layout.fillWidth: true
        onValueChanged: sendPitchRollYawThottle()
    }

    Label {
        text: qsTr("Throttle")
    }

    SpinBox {
        id: throttleBox
        Layout.fillWidth: true
        onValueChanged: sendPitchRollYawThottle()
    }

    Connections {
        target: vehicle
        ignoreUnknownSignals: true
        onAttitudeChanged: {
            updating = true;
            if (!pitchBox.focused) pitchBox.value = attitude.pitch.toFixed(2);
            if (!rollBox.focused) rollBox.value = attitude.roll.toFixed(2);
            if (!yawBox.focused) yawBox.value = attitude.yaw.toFixed(2);
            updating = false;
        }
        onThrottleChanged: {
            updating = true;
            if (!throttleBox.focused) throttleBox.value = throttle.toFixed(0);
            updating = false;
        }
    }

    function sendPitchRollYawThottle() {
        if (!vehicle || updating) return;

        vehicle.commandPitchRollYawThrottle(pitchBox.value, rollBox.value,
                                            yawBox.value, throttleBox.value);
    }
}
