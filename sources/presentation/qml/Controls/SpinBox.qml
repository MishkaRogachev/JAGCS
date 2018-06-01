import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.SpinBox {
    id: control

    property bool isValid: value >= from && value <= to
    property color color: customPalette.textColor
    property color backgroundColor: customPalette.sunkenColor
    property string tipText

    implicitWidth: sizings.controlBaseSize * 5
    implicitHeight: sizings.controlBaseSize
    leftPadding: sizings.controlBaseSize
    rightPadding: sizings.controlBaseSize
    font.pixelSize: sizings.primaryFontSize
    editable: true
    opacity: enabled ? 1 : 0.33

    validator: IntValidator {
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    background: Rectangle {
        radius: 3
        color: isValid ? backgroundColor : customPalette.dangerColor
        border.color: control.activeFocus ? customPalette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: NumericInput {
        text: isValid ? control.textFromValue(control.value, control.locale) : "0"
        color: isValid ? control.color : customPalette.selectedTextColor
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
        color: down.pressed ? customPalette.highlightColor : "transparent"
        visible: enabled

        Rectangle {
            anchors.fill: parent
            color: customPalette.textColor
            radius: parent.radius
            opacity: 0.1
            visible: down.hovered
        }

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/minus.svg"
            color: isValid ? control.color : customPalette.selectedTextColor
            height: parent.height * 0.6
            width: height
        }
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : parent.width - width
        implicitWidth: sizings.controlBaseSize
        implicitHeight: sizings.controlBaseSize
        radius: 3
        color: up.pressed ? customPalette.highlightColor : "transparent"
        visible: enabled

        Rectangle {
            anchors.fill: parent
            color: customPalette.textColor
            radius: parent.radius
            opacity: 0.1
            visible: up.hovered
        }

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/plus.svg"
            color: isValid ? control.color : customPalette.selectedTextColor
            height: parent.height * 0.6
            width: height
        }
    }

    ToolTip {
        visible: (hovered) && tipText
        text: tipText
        delay: 1000
    }
}
