import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.RadioButton {
    id: control

    property alias horizontalAlignment: label.horizontalAlignment

    font.pixelSize: sizings.fontSize
    height: sizings.controlBaseSize
    leftPadding: 0
    spacing: sizings.spacing
    implicitWidth: text.length > 0 ? contentItem.implicitWidth + spacing : indicator.implicitWidth

    indicator: Rectangle {
        implicitWidth: sizings.controlBaseSize * 0.8
        implicitHeight: sizings.controlBaseSize * 0.8
        x: control.leftPadding
        y: parent.height * 0.5 - height * 0.5
        radius: width * 0.5
        color: "transparent"
        border.color: control.activeFocus ? customPalette.highlightColor : customPalette.controlColor

        Rectangle {
            anchors.fill: parent
            anchors.margins: parent.width * 0.25
            radius: width * 0.5
            color: control.down ? customPalette.highlightColor : customPalette.textColor
            visible: control.checked || control.down
        }

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: Label {
        id: label
        text: control.text
        font: control.font
        leftPadding: indicator.width + spacing
        verticalAlignment: Text.AlignVCenter
    }
}
