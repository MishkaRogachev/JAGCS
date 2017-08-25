import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

ComboBox {
    id: control

    font.pixelSize: palette.fontPixelSize
    clip: true
    //enabled: count > 0 TODO: comboBox does not update

    delegate: ItemDelegate {
        width: control.width
        text: modelData
        highlighted: control.highlightedIndex === index
    }

    background: Rectangle {
        implicitWidth: palette.controlBaseSize * 4
        implicitHeight: palette.controlBaseSize
        radius: 3
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    indicator: ColoredIcon {
        visible: control.focus
        x: control.width - width
        y: control.height - height
        width: palette.controlBaseSize / 2
        height: width
        source: "qrc:/ui/menu_arrow.svg"
        color: control.down ? palette.highlightColor : palette.selectionColor
    }

    contentItem: Text {
        text: control.displayText
        verticalAlignment: Text.AlignVCenter
        font: control.font
        color: palette.textColor
    }
}
