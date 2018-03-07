import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

T.SpinBox {
    id: control

    property bool isValid: value >= from && value <= to
    property color backgroundColor: palette.sunkenColor

    font.pixelSize: sizings.fontPixelSize
    editable: true
    implicitWidth: sizings.controlBaseSize * 5
    implicitHeight: sizings.controlBaseSize
    opacity: enabled ? 1 : 0.33

    validator: IntValidator {
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: isValid ? backgroundColor : palette.dangerColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: NumericInput {
        text: isValid ? control.textFromValue(control.value, control.locale) : "0"
        font: control.font
        readOnly: !control.editable
        inputMethodHints: Qt.ImhDigitsOnly
        validator: control.validator
        verticalAlignment: Qt.AlignVCenter
    }

    down.indicator: Rectangle {
        x: control.mirrored ? parent.width - width : 0
        implicitWidth: sizings.controlBaseSize
        implicitHeight: sizings.controlBaseSize
        radius: 3
        color: down.pressed ? palette.highlightColor : "transparent"
        opacity: enabled ? 1 : 0.33

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/minus.svg"
            color: palette.textColor
            height: parent.height * 0.6
            width: height
        }
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : parent.width - width
        implicitWidth: sizings.controlBaseSize
        implicitHeight: sizings.controlBaseSize
        radius: 3
        color: up.pressed ? palette.highlightColor : "transparent"
        opacity: enabled ? 1 : 0.33

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/plus.svg"
            height: parent.height * 0.6
            width: height
            color: palette.textColor
        }
    }
}
