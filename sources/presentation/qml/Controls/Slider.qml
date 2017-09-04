import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Slider {
    id: control

    property real visualValue: from + position * (to - from)

    height: palette.controlBaseSize
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: palette.controlBaseSize * 6
        implicitHeight: palette.controlBaseSize / 4
        width: control.availableWidth
        height: implicitHeight
        radius: height / 2
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: palette.selectionColor
            radius: height / 2
        }

        // TODO: hatch
    }

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: palette.controlBaseSize / 1.5
        implicitHeight: implicitWidth
        radius: width / 2
        color: palette.highlightColor
        visible: enabled

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
