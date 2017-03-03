import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property alias useJoystick: useJoystickBox.checked

    signal setUseJoystick(bool use)

    GridLayout {
        anchors.fill: parent
        rowSpacing: palette.spacing
        columns: 2

        Label {
            text: qsTr("Use joystick")
            Layout.fillWidth: true
        }

        CheckBox {
            id: useJoystickBox
            onCheckedChanged: setUseJoystick(checked)
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
