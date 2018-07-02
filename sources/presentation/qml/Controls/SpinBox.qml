import QtQuick 2.6
import QtQuick.Templates 2.2 as T

T.SpinBox {
    id: control

    property bool isValid: value >= from && value <= to
    property color color: customPalette.textColor

    property alias backgroundColor: background.color
    property alias labelText: background.text

    implicitWidth: background.implicitWidth
    implicitHeight: background.implicitHeight
    leftPadding: sizings.controlBaseSize
    rightPadding: sizings.controlBaseSize
    font.pixelSize: sizings.fontSize
    editable: true
    opacity: enabled ? 1 : 0.33

    validator: IntValidator {
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    background: BackgroundItem {
        id: background
        anchors.fill: parent
        leftPadding: sizings.controlBaseSize + sizings.padding
        color: isValid ? "transparent" : customPalette.dangerColor
        textColor: isValid ? (highlighted ? customPalette.highlightColor :
                                            customPalette.secondaryTextColor) :
                             customPalette.selectedTextColor
        highlighted: control.activeFocus
    }

    contentItem: NumericInput {
        text: isValid ? control.textFromValue(control.value, control.locale) : "0"
        color: isValid ? control.color : customPalette.selectedTextColor
        font: control.font
        readOnly: !control.editable
        inputMethodHints: Qt.ImhDigitsOnly
        validator: control.validator
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: labelText.length > 0 ? Text.AlignBottom : Text.AlignVCenter
        bottomPadding: background.offset
    }

    down.indicator: Rectangle {
        x: control.mirrored ? parent.width - width : 0
        width: sizings.controlBaseSize
        height: parent.height - background.radius
        radius: 3
        color: down.pressed ? customPalette.highlightColor : "transparent"
        opacity: enabled ? 1 : 0.33

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
            color: isValid && !down.pressed ? control.color :
                                              customPalette.selectedTextColor
            width: parent.width * 0.6
            height: width
        }
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : parent.width - width
        width: sizings.controlBaseSize
        height: parent.height - background.radius
        radius: 3
        color: up.pressed ? customPalette.highlightColor : "transparent"
        opacity: enabled ? 1 : 0.33

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
            color: isValid && !up.pressed ? control.color :
                                            customPalette.selectedTextColor
            width: parent.width * 0.6
            height: width
        }
    }
}
