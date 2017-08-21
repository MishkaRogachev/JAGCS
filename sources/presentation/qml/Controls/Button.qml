import QtQuick 2.6
import QtQuick.Controls 2.0 // TODO:QtQuick.Templates

import "./" as Custum

Control {
    id: control

    property bool checkable: false
    property bool checked: false
    property string text

    property alias pressed: area.pressed
    property alias iconSource: icon.source
    property alias iconColor: icon.color
    property alias textColor: label.color
    property alias backgroundColor: backgroundItem.color

    signal clicked()
    signal released()

    font.pixelSize: palette.fontPixelSize
    implicitWidth: Math.max(backgroundItem.implicitWidth, content.implicitWidth)
    implicitHeight: Math.max(backgroundItem.implicitHeight, content.implicitHeight)

    background: Rectangle {
        id: backgroundItem
        implicitWidth: palette.controlBaseSize
        implicitHeight: palette.controlBaseSize
        border.color: control.activeFocus ? palette.highlightColor : "transparent"
        color: {
            if (control.checked) return palette.selectionColor;
            if (!enabled) return palette.disabledColor;
            if (control.pressed) return palette.highlightColor;
            return control.flat ? "transparent" : palette.buttonColor;
        }
    }

    contentItem: Item { // TODO: common content item
        id: content
        implicitWidth: row.width
        implicitHeight: row.height

        Row {
            id: row
            anchors.centerIn: parent
            height: parent.availableHeight
            spacing: palette.spacing

            ColoredIcon {
                id: icon
                color: label.color
                anchors.verticalCenter: parent.verticalCenter
                height: control.height * 0.6
                width: height
                visible: source != ""
            }

            Label {
                id: label
                font: control.font
                text: control.text
                color: control.pressed || control.checked ?
                           palette.selectedTextColor: palette.textColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onClicked: {
                control.clicked();
                if (checkable) checked = !checked;
            }
            onReleased: control.released()
        }
    }
}
