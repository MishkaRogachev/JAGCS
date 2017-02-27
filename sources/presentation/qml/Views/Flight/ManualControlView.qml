import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

GridLayout {
    id: root

    enabled: vehicle
    columns: 2

    Label {
        text: qsTr("Pitch")
    }

    SpinBox {
        id: pitchBox
        onValueChanged: if (vehicle && value !== vehicle.attitude.pitch.toFixed(2))
                            sendPitchRollYawThottle()
    }

    Label {
        text: qsTr("Roll")
    }

    SpinBox {
        id: rollBox
        onValueChanged: if (vehicle && value !== vehicle.attitude.roll.toFixed(2))
                            sendPitchRollYawThottle()
    }

    Label {
        text: qsTr("Yaw")
    }

    SpinBox {
        id: yawBox
        onValueChanged: if (vehicle && value !== vehicle.attitude.yaw.toFixed(2))
                            sendPitchRollYawThottle()
    }

    Label {
        text: qsTr("Throttle")
    }

    SpinBox {
        id: throttleBox
        onValueChanged: if (vehicle && value !== vehicle.throttle.toFixed(0))
                            sendPitchRollYawThottle()
    }

    Connections {
        target: vehicle
        ignoreUnknownSignals: true
        onAttitudeChanged: {
            if (!pitchBox.focused) pitchBox.value = attitude.pitch.toFixed(2);
            if (!rollBox.focused) rollBox.value = attitude.roll.toFixed(2);
            if (!yawBox.focused) yawBox.value = attitude.yaw.toFixed(2);
        }
        onThrottleChanged: {
            if (!throttleBox.focused) throttleBox.value = throttle.toFixed(0);
        }
    }

    function sendPitchRollYawThottle() {
        vehicle.commandPitchRollYawThrottle(pitchBox.value, rollBox.value,
                                            yawBox.value, throttleBox.value);
    }
}
