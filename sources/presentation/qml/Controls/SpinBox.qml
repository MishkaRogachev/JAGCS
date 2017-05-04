import QtQuick 2.6
import QtQuick.Controls 2.0

import "./" as Custom

SpinBox {
    id: control

    property bool isValid: value >= from && value <= to

    font.pixelSize: palette.fontPixelSize
    editable: true
    padding: 0

    background: Rectangle {
        implicitWidth: palette.controlBaseSize * 6
        implicitHeight: palette.controlBaseSize
        color: {
            if (!control.enabled) return palette.disabledColor;
            if (!isValid) return palette.negativeColor;
            return palette.sunkenColor;
        }
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
    }

    contentItem: TextInput {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -(up.indicator.width +
                                          down.indicator.width) / 2
        text: isValid ? control.textFromValue(control.value, control.locale) : "NaN"
        font: control.font
        readOnly: !control.editable
        validator: control.validator
        color: palette.textColor
        selectionColor: palette.selectionColor
        selectedTextColor: palette.selectedTextColor
        selectByMouse: true
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        inputMethodHints: Qt.ImhFormattedNumbers
    }

    down.indicator: Rectangle {
        x: control.mirrored ? up.indicator.width : control.width - width - up.indicator.width
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        color: down.pressed ? palette.highlightColor : "transparent"

        Custom.ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/minus.svg"
            color: enabled ? palette.textColor : palette.disabledColor
            height: parent.height * 0.6
            width: height
        }
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : control.width - width
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        color: up.pressed ? palette.highlightColor : "transparent"
        visible: enabled

        Custom.ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/plus.svg"
            height: parent.height * 0.6
            width: height
            color: enabled ? palette.textColor : palette.disabledColor
        }
    }
}
