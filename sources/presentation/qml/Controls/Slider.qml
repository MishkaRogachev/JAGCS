import QtQuick 2.6
import QtQuick.Templates 2.2 as T

T.Slider {
    id: control

    property real visualValue: from + position * (to - from)

    height: sizings.controlBaseSize
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: sizings.controlBaseSize * 6
        width: control.availableWidth
        height: 2
        radius: height / 2
        color: customPalette.controlColor

        Rectangle {
            width: control.visualPosition * parent.width
            height: parent.height
            color: customPalette.selectionColor
            radius: height / 2
        }
    }

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: sizings.controlBaseSize / 1.5
        implicitHeight: implicitWidth
        radius: width / 2
        color: control.activeFocus ? customPalette.highlightColor : customPalette.buttonColor
        visible: enabled

        Shadow {
            source: parent
        }

        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 2
            height: width
            radius: width / 2
            color: customPalette.highlightColor
            opacity: 0.5
            visible: control.pressed
        }
    }

    ToolTip {
        parent: handle
        visible: hovered || pressed
        text: visualValue.toFixed(0)
    }
}
