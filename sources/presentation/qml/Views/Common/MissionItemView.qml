import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: root

    property bool selected: false
    property bool current: false
    property bool reached: false
    property int status: MissionItem.NotActual
    property int command: MissionItem.UnknownCommand
    property int sequence: -1

    property alias selectionAvalible: area.visible

    signal selectionRequest()
    signal holded()

    implicitWidth: palette.controlBaseSize
    implicitHeight: palette.controlBaseSize
    radius: height / 2
    border.width: width / 10
    color: selected ? palette.selectionColor : palette.raisedColor
    border.color: {
        if (current) return palette.activeMissionColor; // TODO: highlight current only in mission
        if (reached) return palette.positiveColor;

        switch (status) {
        case MissionItem.Actual: return palette.missionColor;
        case MissionItem.StatusNone: return palette.sunkenColor;
        case MissionItem.Downloading:
        case MissionItem.Uploading: return palette.cautionColor;
        case MissionItem.NotActual:
        default: return palette.dangerColor;
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
        color: palette.textColor
        visible: source != ""
        width: parent.width * 0.6
        height: parent.height * 0.6
    }

    Controls.Label {
        visible: !icon.visible
        text: sequence
        color: palette.textColor
        anchors.centerIn: parent
        font.bold: true
    }

    MouseArea {
        id: area
        anchors.fill: parent
        onPressed: selectionRequest()
        onPressAndHold: holded()
    }
}
