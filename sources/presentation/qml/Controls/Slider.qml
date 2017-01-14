import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Slider {
    id: control

    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: palette.controlBaseWidth
        implicitHeight: palette.controlBaseSize / 4
        width: control.availableWidth
        height: implicitHeight
        radius: height / 2
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: palette.selectionColor
            radius: height / 2
        }
    }

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: palette.controlBaseSize / 1.5
        implicitHeight: implicitWidth
        radius: width / 2
        color: palette.highlightColor

        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 2
            height: width
            radius: width / 2
            color: palette.highlightColor
            opacity: 0.5
            visible: control.pressed
        }
    }
}
/*
Slider {
    id: control

    background: Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        implicitWidth: control.availableWidth
        implicitHeight: palette.controlBaseSize / 4
        height: implicitHeight
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
        implicitWidth: control.pressed ? palette.controlBaseSize :
                                         palette.controlBaseSize / 1.5
        implicitHeight: implicitWidth
        radius: width / 2
        color: palette.highlightColor
    }
}
*/
