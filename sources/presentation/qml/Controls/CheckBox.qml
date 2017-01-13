import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "./"

CheckBox {
    id: control

    font.pointSize: palette.fontSize

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
            sourceSize.height: control.height * 0.6
            sourceSize.width: sourceSize.height
            color: control.down ? palette.highlightColor : palette.selectionColor
            visible: control.checked
        }
    }

    contentItem: Label {
        text: control.text
        font: control.font
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
