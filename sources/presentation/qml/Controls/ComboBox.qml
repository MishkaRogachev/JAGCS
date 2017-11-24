import QtQuick 2.6
import QtQuick.Templates 2.1 as T
import QtQuick.Layouts 1.3

import "../Shaders" as Shaders

T.ComboBox {
    id: control

    // TODO: fix dynamic width calculation
    property var currentItem: model && model[currentIndex] ? model[currentIndex] : undefined
    property string tipText
    property string iconRole: "icon"
    property string displayIcon: currentItem && currentItem[control.iconRole] !== undefined ?
                                     currentItem[control.iconRole] : ""

    font.pixelSize: sizings.fontPixelSize
    clip: true
    implicitWidth: sizings.controlBaseSize * 4
    implicitHeight: sizings.controlBaseSize
    opacity: enabled ? 1 : 0.33
    displayText: currentItem && currentItem[control.textRole] !== undefined ?
                     currentItem[control.textRole] : currentItem

    indicator: ColoredIcon {
        visible: control.focus
        x: control.width - width
        y: control.height - height
        width: sizings.controlBaseSize / 2
        height: width
        source: "qrc:/ui/menu_arrow.svg"
        color: control.down ? palette.highlightColor : palette.selectionColor
    }

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: palette.sunkenColor
        border.color: control.activeFocus ? palette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    delegate: ItemDelegate {
        width: control.width
        text: modelData[control.textRole] !== undefined ? modelData[control.textRole] : modelData
        iconSource: modelData[iconRole] !== undefined ? modelData[iconRole] : ""
        highlighted: control.highlightedIndex === index
    }

    contentItem: RowLayout {
        ContentItem {
            text: displayText
            iconSource: displayIcon
            font: control.font
            Layout.margins: sizings.padding
        }

        Item { Layout.fillWidth: true }
    }

    popup: Popup {
        y: control.height
        width: control.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {}
        }
    }

    ToolTip {
        visible: hovered && tipText
        text: tipText
        delay: 1000
    }
}
