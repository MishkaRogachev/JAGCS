import QtQuick 2.6
import QtQuick.Templates 2.0 as T
import QtQuick.Layouts 1.3

T.ItemDelegate {
    id: control

    property alias iconSource: content.iconSource

    font.pixelSize: sizings.fontPixelSize
    implicitWidth: content.implicitWidth
    implicitHeight: sizings.controlBaseSize

    contentItem: RowLayout {
        ContentItem {
            id: content
            font: control.font
            text: control.text
            textColor: control.highlighted ? palette.selectedTextColor : palette.textColor
            Layout.leftMargin: sizings.padding
        }

        Item { Layout.fillWidth: true }
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
