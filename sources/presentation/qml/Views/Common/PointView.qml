import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: pointView

    property bool selected: false
    property bool current: false
    property bool reached: false
    property int sequence: -1
    property int status: MissionItem.NotActual
    property int command: MissionItem.UnknownCommand

    property alias selectionAvalible: area.visible

    signal selectionRequest()
    signal holded()

    implicitWidth: sizings.controlBaseSize
    implicitHeight: sizings.controlBaseSize
    radius: height / 2
    border.width: sizings.controlBaseSize / 10
    color: selected ? customPalette.selectionColor : customPalette.raisedColor
    border.color: {
        if (current) return customPalette.activeMissionColor; // TODO: highlight current only in mission
        if (reached) return customPalette.positiveColor;

        switch (status) {
        case MissionItem.Actual: return customPalette.missionColor;
//        case MissionItem.StatusNone: return customPalette.sunkenColor;
        case MissionItem.NotActual:
        default: return customPalette.dangerColor;
        }
    }

    Controls.ColoredIcon {
        id: icon
        anchors.centerIn: parent
        source: {
            switch (command) {
            case MissionItem.Home:
                return "qrc:/icons/home.svg";
            case MissionItem.Takeoff:
                return "qrc:/icons/takeoff.svg";
            case MissionItem.Landing:
                return "qrc:/icons/landing.svg";
            case MissionItem.TargetPoint:
                return "qrc:/icons/aim.svg";
            default:
                return "";
            }
        }
        color: customPalette.textColor
        visible: source != ""
        width: parent.width * 0.6
        height: parent.height * 0.6
    }

    Controls.Label {
        visible: !icon.visible
        text: sequence + 1
        color: customPalette.textColor
        anchors.centerIn: parent
        font.bold: true
    }

    MouseArea {
        id: area
        anchors.fill: parent
        onPressed: selectionRequest()
    }
}

