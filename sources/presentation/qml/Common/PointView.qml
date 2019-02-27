import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

Rectangle {
    id: point

    property bool selected: false
    property bool current: false
    property bool reached: false
    property int sequence: -1
    property int status: MissionItem.NotActual
    property int command: MissionItem.UnknownCommand

    implicitWidth: industrial.baseSize
    implicitHeight: industrial.baseSize
    radius: height / 2
    border.width: industrial.baseSize / 10
    color: selected ? industrial.colors.selection : industrial.colors.surface
    border.color: {
        if (current) return Indicators.Theme.activeColor;
        if (reached) return Indicators.Theme.positiveColor;

        switch (status) {
        case MissionItem.Actual: return industrial.colors.highlight;
        case MissionItem.StatusNone: return industrial.colors.onSurface;
        case MissionItem.NotActual:
        default: return Indicators.Theme.dangerColor;
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
        color: industrial.colors.onSurface
        visible: source != ""
        width: parent.width * 0.6
        height: parent.height * 0.6
    }

    Controls.Label {
        visible: !icon.visible
        text: sequence + 1
        color: industrial.colors.onSurface
        anchors.centerIn: parent
        font.bold: true
    }
}

