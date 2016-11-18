import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

SpinBox {
    id: control

    font.pointSize: palette.fontSize

    leftPadding: padding * 2
    rightPadding: padding + down.indicator.width + up.indicator.width

    contentItem: TextInput {
        text: textFromValue(control.value, control.locale)
        onEditingFinished:control.value = valueFromText(text, control.locale)
        font: control.font
        color: palette.textColor
        selectionColor: palette.selectionColor
        selectedTextColor: palette.selectedTextColor
        verticalAlignment: Qt.AlignVCenter
        validator: control.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    background: Rectangle {
        implicitWidth: palette.controlBaseWidth
        implicitHeight: palette.controlBaseSize
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
    }

    down.indicator: Rectangle {
        x: control.mirrored ? up.indicator.width :
                              control.width - width - up.indicator.width
        height: control.height
        implicitWidth: palette.controlBaseSize
        implicitHeight: implicitWidth
        color: down.pressed ? palette.highlightColor : "transparent"

        Image {
            anchors.centerIn: parent
            opacity: enabled ? 1 : 0.5
            source: "qrc:/icons/minus.svg"
        }
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : control.width - width
        height: control.height
        implicitWidth: palette.controlBaseSize
        implicitHeight: implicitWidth
        color: up.pressed ? palette.highlightColor : "transparent"

        Image {
            anchors.centerIn: parent
            opacity: enabled ? 1 : 0.5
            source: "qrc:/icons/plus.svg"
        }
    }
}
