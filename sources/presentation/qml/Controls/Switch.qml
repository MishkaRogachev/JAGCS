import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.Switch {
    id: control

    property bool inputChecked: checked
    property alias textColor: text.color
    property alias backgroundColor: backgroundItem.color
    property string tipText

    spacing: sizings.spacing
    font.pixelSize: sizings.fontSize
    implicitWidth: contentItem.implicitWidth
    implicitHeight: sizings.controlBaseSize

    onInputCheckedChanged: if (checked != inputChecked) checked = inputChecked

    indicator: Rectangle {
        id: backgroundItem
        implicitWidth: sizings.controlBaseSize
        implicitHeight: sizings.controlBaseSize / 4
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: height / 2
        border.color: control.activeFocus ? customPalette.highlightColor : "transparent"
        color: control.inputChecked ? customPalette.selectionColor : customPalette.sunkenColor;

        Rectangle {
            x: control.checked ? parent.width - width : 0
            anchors.verticalCenter: parent.verticalCenter
            width: sizings.controlBaseSize / 1.5
            height: sizings.controlBaseSize / 1.5
            radius: height / 2
            color: control.pressed ? customPalette.highlightColor : customPalette.buttonColor;

            Shaders.Hatch {
                anchors.fill: parent
                color: customPalette.sunkenColor
                visible: !control.enabled
            }
        }
    }

    contentItem: Text {
        id: text
        horizontalAlignment: Qt.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text: control.text
        font: control.font
        color: customPalette.textColor
        leftPadding: indicator.width + control.spacing
    }

    ToolTip {
        visible: (hovered || down) && tipText
        text: tipText
        delay: 1000
    }
}
