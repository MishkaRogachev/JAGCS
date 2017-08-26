import QtQuick 2.6
import QtQuick.Templates 2.0 as T
import QtQuick.Layouts 1.3

T.CheckBox {
    id: control

    font.pixelSize: palette.fontPixelSize
    height: palette.controlBaseSize
    leftPadding: 0
    spacing: palette.spacing
    implicitWidth: text.length > 0 ? contentItem.implicitWidth + spacing : indicator.implicitWidth

    indicator: Rectangle {
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        ColoredIcon {
            anchors.centerIn: parent
            source: "qrc:/ui/ok.svg"
            height: control.height * 0.6
            width: height
            color: control.down ? palette.highlightColor : palette.textColor
            visible: control.checked || control.down
        }

        Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: Label {
        text: control.text
        font: control.font
        leftPadding: indicator.width + spacing
        verticalAlignment: Text.AlignVCenter
    }
}
