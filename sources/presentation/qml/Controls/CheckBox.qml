import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "./"

CheckBox {
    id: control

    font.pixelSize: palette.fontPixelSize
    height: palette.controlBaseSize

    indicator: Rectangle {
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        color: control.enabled ? palette.sunkenColor : palette.disabledColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/ok.svg"
            height: control.height * 0.6
            width: height
            color: control.down ? palette.highlightColor : palette.textColor
            visible: control.checked || control.down
        }
    }

    contentItem: Label {
        text: control.text
        font: control.font
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + (text.length > 0 ?
                                                    control.spacing :
                                                    -control.spacing)
    }
}
