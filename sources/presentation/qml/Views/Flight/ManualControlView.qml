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
        text: qsTr("R")
    }

    Slider {
        id: r
        Layout.fillWidth: true
        from: -1000
        to: 1000
        onPressedChanged: if (vehicle && !pressed) sendManualInput()
    }

    // TODO: feedback Connections

    function sendManualInput() {
        vehicle.commandManualInput(x.position, y.position,
                                   z.position, r.position);
    }
}
