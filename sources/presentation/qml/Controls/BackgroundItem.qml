import QtQuick 2.6

import "../Shaders" as Shaders

Rectangle {
    id: control

    property bool inputed: true
    property bool highlighted: false
    property int leftPadding: sizings.padding
    readonly property int offset: radius + 1

    property alias text: textItem.text
    property alias textColor: textItem.color

    implicitWidth: Math.max(sizings.controlBaseSize * 4, textItem.implicitWidth)
    implicitHeight: sizings.inputControlHeight
    radius: 3
    color: customPalette.sunkenColor

    Rectangle {
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.radius
        color: highlighted ? customPalette.highlightColor : customPalette.buttonColor
        visible: enabled
    }

    Shaders.Hatch {
        anchors.fill: parent
        color: customPalette.sunkenColor
        visible: !enabled
    }

    Text {
        id: textItem
        anchors.left: parent.left
        anchors.leftMargin: control.leftPadding
        height: parent.height
        verticalAlignment: inputed ? Text.AlignTop : Text.AlignVCenter
        color: highlighted ? customPalette.highlightColor : customPalette.secondaryTextColor
        font.pixelSize: inputed ? sizings.secondaryFontSize: sizings.fontSize
    }
}
