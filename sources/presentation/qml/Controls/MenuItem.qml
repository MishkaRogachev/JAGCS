import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

MenuItem {
    id: control

    property alias iconSource: icon.source
    property color iconColor: label.color

    font.pixelSize: palette.fontPixelSize

    background: Rectangle {
        implicitWidth: palette.controlBaseSize
        implicitHeight: implicitWidth
        color: control.pressed ? palette.highlightColor : "transparent"
        border.color: control.activeFocus ? palette.selectionColor : "transparent"
    }

    indicator: ColoredIcon {
        id: icon
        color: iconColor
        source: control.checked ? "qrc:/ui/ok.svg" : ""
        anchors.verticalCenter: parent.verticalCenter
        width: palette.controlBaseSize
        height: width
    }

    contentItem: Label {
        id: label
        leftPadding: icon.width
        font: control.font
        text: control.text
        color: control.pressed ? palette.selectedTextColor: palette.textColor
    }
}
