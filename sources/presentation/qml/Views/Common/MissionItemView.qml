import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: root

    property bool selected: false
    property bool current: false
    property var item

    signal selectionRequest()

    implicitWidth: palette.controlBaseSize
    implicitHeight: palette.controlBaseSize
    radius: height / 2
    border.width: width / 10
    color: selected ? palette.selectionColor : palette.raisedColor
    border.color: {
        switch (item.status) {
        case MissionItem.Actual:
            if (current) return palette.activeMissionColor;
            if (item.reached) return palette.positiveColor;
            return palette.missionColor;
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
            switch (item.command) {
            case MissionItem.Home:
                return "qrc:/icons/home.svg";
            case MissionItem.Takeoff:
                return "qrc:/icons/takeoff.svg";
            case MissionItem.Landing:
                return "qrc:/icons/landing.svg";
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
        text: item.sequence
        color: palette.textColor
        anchors.centerIn: parent
        font.bold: true
    }

    MouseArea {
        anchors.fill: parent
        onPressed: selectionRequest()
    }
}
