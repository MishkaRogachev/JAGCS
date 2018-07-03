import QtQuick 2.6
import QtQuick.Controls 2.2 as T

import "../Shaders" as Shaders

T.MenuItem {
    id: control

    property alias iconSource: icon.source
    property color iconColor: label.color

    leftPadding: icon.visible ? icon.width + sizings.padding * 2 : 0
    font.pixelSize: sizings.fontSize
    width: parent.width

    background: Rectangle {
        anchors.fill: control
        implicitWidth: sizings.controlBaseSize
        implicitHeight: implicitWidth
        color: {
            if (control.pressed) return customPalette.highlightColor;
            if (control.checked || control.highlighted) return customPalette.selectionColor;
            return "transparent";
        }
        border.color: control.activeFocus ? customPalette.selectionColor : "transparent"
    }

    Rectangle {
        anchors.fill: parent
        color: customPalette.textColor
        opacity: 0.1
        visible: control.hovered
    }

    Shaders.Hatch {
        anchors.fill: parent
        color: customPalette.sunkenColor
        visible: !control.enabled
    }

    indicator: ColoredIcon {
        x: sizings.padding
        id: icon
        color: enabled ? iconColor : customPalette.sunkenColor
        source: control.checked ? "qrc:/ui/ok.svg" : ""
        anchors.verticalCenter: parent.verticalCenter
        width: sizings.controlBaseSize * 0.6
        height: width
    }

    contentItem: Label {
        id: label
        font: control.font
        text: control.text
        color: {
            if (!enabled) return customPalette.sunkenColor;
            if (control.pressed) return customPalette.selectedTextColor;
            return customPalette.textColor;
        }
    }
}
