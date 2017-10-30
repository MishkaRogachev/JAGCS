import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.ToolTip {
    id: control

//    implicitHeight: palette.controlBaseSize
//    implicitWidth: label.implicitWidth + palette.margins * 2

    contentItem: Label {
        text: control.text
        font: control.font
        horizontalAlignment: Qt.AlignHCenter
    }

    background: Rectangle {
        color: palette.raisedColor
        border.color: palette.highlightColor
        radius: 3
    }
}
