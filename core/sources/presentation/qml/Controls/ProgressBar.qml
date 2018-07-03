import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

T.ProgressBar {
    id: control

    property string text: control.visualPosition

    implicitWidth: sizings.controlBaseSize * 4
    implicitHeight: sizings.controlBaseSize
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        anchors.fill: parent
        radius: 2
        color: customPalette.sunkenColor

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled && !control.flat
        }
    }

    contentItem: Item {
        anchors.fill: parent
        anchors.margins: 1

        Rectangle {
            width: control.visualPosition * background.width
            height: parent.height
            radius: 2
            color: customPalette.selectionColor
        }

        Label {
            anchors.centerIn: parent
            text: control.text
        }
    }
}
