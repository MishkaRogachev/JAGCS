import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.ComboBox {
    id: control

    font.pixelSize: palette.fontPixelSize
    clip: true
    implicitWidth: palette.controlBaseSize * 4
    implicitHeight: palette.controlBaseSize
    opacity: enabled ? 1 : 0.33

    delegate: ItemDelegate {
        width: control.width
        text: modelData
        highlighted: control.highlightedIndex === index
    }

    background: Rectangle {
        anchors.fill: parent
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
        padding: palette.margins
        verticalAlignment: Text.AlignVCenter
        font: control.font
        color: palette.textColor
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar { }
        }
    }
}
