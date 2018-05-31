import QtQuick 2.6
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders

Button {
    id: control

    property real radius: Math.min(width, height) / 2

    implicitWidth: sizings.controlBaseSize * 1.2
    implicitHeight: implicitWidth
    round: true
    highlighted: true
}
