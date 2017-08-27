import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.SpinBox {
    id: control

    property bool isValid: value >= from && value <= to

    font.pixelSize: palette.fontPixelSize
    editable: true
    implicitWidth: palette.controlBaseSize * 4
    implicitHeight: palette.controlBaseSize
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: TextInput {
        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -(up.indicator.width + down.indicator.width) / 2
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
    }

    down.indicator: Rectangle {
        x: control.mirrored ? up.indicator.width : control.width - width - up.indicator.width
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        radius: 3
        color: down.pressed ? palette.highlightColor : "transparent"
        visible: enabled

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/minus.svg"
            color: palette.textColor
            height: parent.height * 0.6
            width: height
        }
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : control.width - width
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        radius: 3
        color: up.pressed ? palette.highlightColor : "transparent"
        visible: enabled

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/plus.svg"
            height: parent.height * 0.6
            width: height
            color: palette.textColor
        }
    }
}
