import QtQuick 2.6
import QtQuick.Templates 2.2 as T
import QtQuick.Layouts 1.3

import "../Shaders" as Shaders

T.CheckBox {
    id: control

    property alias horizontalAlignment: label.horizontalAlignment

    font.pixelSize: sizings.fontSize
    height: sizings.controlBaseSize
    leftPadding: 0
    spacing: sizings.spacing
    implicitWidth: text.length > 0 ? contentItem.implicitWidth + spacing : indicator.implicitWidth
    implicitHeight: contentItem.height
    opacity: enabled ? 1 : 0.33

    indicator: Rectangle {
        implicitWidth: sizings.controlBaseSize
        implicitHeight: sizings.controlBaseSize
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 2
        color: "transparent"
        border.color: control.activeFocus ? customPalette.highlightColor : customPalette.controlColor

        ColoredIcon {
            anchors.fill: parent
            anchors.margins: parent.width * 0.1
            source: "qrc:/ui/ok.svg"
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
