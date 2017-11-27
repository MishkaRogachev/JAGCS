import QtQuick 2.6
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders

T.ProgressBar {
    id: control

    property string text: control.visualPosition

    implicitWidth: sizings.controlBaseSize * 4
    implicitHeight: sizings.controlBaseSize
    opacity: enabled ? 1 : 0.33

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: palette.sunkenColor

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled && !control.flat
        }
    }

    contentItem: Item {
        anchors.fill: parent

        Rectangle {
            width: control.visualPosition * background.width
            height: parent.height
            radius: height / 2
            color: palette.selectionColor
        }

        Label {
            anchors.centerIn: parent
            text: control.text
        }
    }
}
