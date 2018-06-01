import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.TextField {
    id: control

    readonly property bool inputed: displayText.length > 0 || activeFocus

    implicitWidth: sizings.controlBaseSize * 4
    implicitHeight: sizings.controlBaseSize * 1.25
    font.pixelSize: sizings.primaryFontSize
    color: customPalette.textColor
    selectionColor: customPalette.selectionColor
    selectedTextColor: customPalette.selectedTextColor
    selectByMouse: true
    leftPadding: sizings.padding
    bottomPadding: 4
    verticalAlignment: Text.AlignBottom
    opacity: enabled ? 1 : 0.33
    placeholderText: "text!"

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: customPalette.sunkenColor

        Rectangle {
            anchors.bottom: parent.bottom
            color: control.activeFocus ? customPalette.highlightColor : customPalette.buttonColor
            width: parent.width
            height: parent.radius
        }

        Text {
            anchors.left: parent.left
            anchors.leftMargin: control.leftPadding
            height: parent.height
            verticalAlignment: inputed ? Text.AlignTop : Text.AlignVCenter
            text: placeholderText
            color: control.activeFocus ? customPalette.highlightColor : customPalette.buttonColor
            font.pixelSize: sizings.secondaryFontSize
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled
        }
    }
}
