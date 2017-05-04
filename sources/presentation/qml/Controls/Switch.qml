import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Switch {
    id: control

    property bool inputChecked: checked
    property alias textColor: text.color

    font.pixelSize: palette.fontPixelSize

    onInputCheckedChanged: if (checked != inputChecked) checked = inputChecked

    indicator: Rectangle {
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize / 4
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: height / 2
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        color: {
            if (control.inputChecked) return palette.selectionColor;
            if (!enabled) return palette.disabledColor;
            return palette.sunkenColor ;
        }

        Rectangle {
            x: control.checked ? parent.width - width : 0
            anchors.verticalCenter: parent.verticalCenter
            width: palette.controlBaseSize / 1.5
            height: palette.controlBaseSize / 1.5
            radius: height / 2
            color: {
                if (!enabled) return palette.disabledColor;
                if (control.pressed) return palette.highlightColor;
                return palette.buttonColor;
            }
        }
    }

    contentItem: Text {
        id: text
        text: control.text
        font: control.font
        color: palette.textColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
