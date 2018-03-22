import QtQuick 2.6
import QtQuick.Controls 2.2 as T

import "../Shaders" as Shaders

T.MenuItem {
    id: control

    property alias iconSource: icon.source
    property color iconColor: label.color

    leftPadding: icon.width
    font.pixelSize: sizings.fontPixelSize

    background: Rectangle {
        implicitWidth: sizings.controlBaseSize
        implicitHeight: implicitWidth
        color: control.pressed ? customPalette.highlightColor : "transparent"
        border.color: control.activeFocus ? customPalette.selectionColor : "transparent"
    }

    Shaders.Hatch {
        anchors.fill: parent
        color: customPalette.sunkenColor
        visible: !control.enabled
    }

    indicator: ColoredIcon {
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
            pressed || checked || highlighted ? customPalette.selectedTextColor: customPalette.textColor;
        }
    }
}
