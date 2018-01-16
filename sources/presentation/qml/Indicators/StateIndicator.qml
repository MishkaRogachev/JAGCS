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
        case Domain.Active: return palette.missionColor;
        case Domain.Boot:
        case Domain.Calibrating: return palette.selectionColor;
        case Domain.Critical: return palette.dangerColor;
        case Domain.Emergency: return palette.cautionColor;
        case Domain.Standby: return palette.positiveColor;
        case Domain.UnknownState:
        default: return palette.sunkenColor;
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
