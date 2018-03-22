import QtQuick 2.6
import JAGCS 1.0

import "../Controls" as Controls

Rectangle {
    id: root

    property int state: Domain.UnknownState

    onStateChanged: icon.source = translator.imageFromVehicleState(state)

    implicitWidth: sizings.controlBaseSize
    implicitHeight: width
    radius: Math.max(width, height) / 2
    color: {
        switch (state) {
        case Domain.Active: return customPalette.missionColor;
        case Domain.Boot:
        case Domain.Calibrating: return customPalette.selectionColor;
        case Domain.Critical: return customPalette.dangerColor;
        case Domain.Emergency: return customPalette.cautionColor;
        case Domain.Standby: return customPalette.positiveColor;
        case Domain.UnknownState:
        default: return customPalette.sunkenColor;
        }
    }
    Behavior on color { ColorAnimation { duration: 200 } }

    Controls.ColoredIcon {
        id: icon
        source: translator.imageFromVehicleState(state)
        anchors.fill: parent
    }

    MouseArea {
        id: area
        anchors.fill: parent
        hoverEnabled: true
    }

    Controls.ToolTip {
        visible: area.containsMouse
        text: translator.translateVehicleState(state)
        delay: 1000
    }
}
