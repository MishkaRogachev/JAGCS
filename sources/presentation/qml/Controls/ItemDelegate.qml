import QtQuick 2.6
import QtQuick.Templates 2.0 as T
import QtQuick.Layouts 1.3

T.ItemDelegate {
    id: control

    property alias horizontalAlignment: text.horizontalAlignment

    font.pixelSize: sizings.fontPixelSize
    implicitWidth: text.implicitWidth
    implicitHeight: sizings.controlBaseSize
    padding: sizings.padding

    contentItem: Text {
        id: text
        font: control.font
        text: control.text
        color: control.highlighted ? palette.selectedTextColor : palette.textColor
    }

    background: Rectangle {
        implicitHeight: sizings.controlBaseSize
        border.color: control.activeFocus ? palette.selectionColor : "transparent"
        color: {
            if (control.down) return palette.highlightColor;
            if (control.highlighted) return palette.selectionColor;
            return palette.sunkenColor;
        }
    }
}
