import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Slider {
    id: control

    implicitHeight: palette.controlBaseSize

    background: Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        width: control.availableWidth
        implicitWidth: palette.controlBaseWidth
        height: control.height / 4
        radius: height / 2

        Rectangle {
            width: control.visualPosition * control.availableWidth
            height: parent.height
            color: palette.selectionColor
            radius: height / 2
        }
    }

    handle: Rectangle {
        x: control.visualPosition * control.availableWidth - width / 2
        anchors.verticalCenter: parent.verticalCenter
        implicitWidth: control.pressed ? control.height :
                                         control.height / 1.5
        implicitHeight: implicitWidth
        radius: width / 2
        color: palette.highlightColor
    }
}
