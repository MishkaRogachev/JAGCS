import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

GridLayout {
    id: root

    property bool updating: false

    enabled: vehicle
    columns: 3

    Label {
        text: qsTr("X")
    }

    Slider {
        id: x
        Layout.fillWidth: true
        from: -1000
        to: 1000
        onPressedChanged: if (vehicle && !pressed) sendManualInput()
    }

    Label {
        text: x.visualValue.toFixed(0)
        horizontalAlignment: Qt.AlignHCenter
        Layout.preferredWidth: palette.controlBaseSize * 1.5
    }

    Label {
        text: qsTr("Y")
    }

    Slider {
        id: y
        Layout.fillWidth: true
        from: -1000
        to: 1000
        onPressedChanged: if (vehicle && !pressed) sendManualInput()
    }

    Label {
        text: y.visualValue.toFixed(0)
        horizontalAlignment: Qt.AlignHCenter
        Layout.preferredWidth: palette.controlBaseSize * 1.5
    }

    Label {
        text: qsTr("Z")
    }

    Slider {
        id: z
        Layout.fillWidth: true
        from: -1000
        to: 1000
        onPressedChanged: if (vehicle && !pressed) sendManualInput()
    }

    Label {
        text: z.visualValue.toFixed(0)
        horizontalAlignment: Qt.AlignHCenter
        Layout.preferredWidth: palette.controlBaseSize * 1.5
    }

    Label {
        text: qsTr("R")
    }

    Slider {
        id: r
        Layout.fillWidth: true
        from: -1000
        to: 1000
        value: -1000
        onPressedChanged: if (vehicle && !pressed) sendManualInput()
    }

    Label {
        text: r.value.toFixed(0)
        horizontalAlignment: Qt.AlignHCenter
        Layout.preferredWidth: palette.controlBaseSize * 1.5
    }

    Connections {
        target: joystick
        ignoreUnknownSignals: true
        onAxisXChanged: x.value = axisX * 1000
        onAxisYChanged: y.value = axisY * 1000
        onAxisZChanged: z.value = axisZ * 1000
        onAxisRChanged: r.value = axisR * 1000
    }

    // TODO: feedback Connections

    function sendManualInput() {
        vehicle.commandManualInput(x.value, y.value, z.value, r.value);
    }
}
