import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: point

    property bool selected: false
    property bool current: false
    property bool reached: false
    property int sequence: -1
    property int status: MissionItem.NotActual
    property int command: MissionItem.UnknownCommand

    property bool dragEnabled: false
    property alias mouseEnabled: area.visible

    signal clicked()
    signal holded()
    signal dragged(real dx, real dy)

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

    Controls.ColoredIcon {
        id: picker
        width: parent.width
        height: parent.height
        source: "qrc:/icons/aim.svg";
        color: customPalette.activeMissionColor
        visible: area.drag.active
    }

    MouseArea {
        id: area
        anchors.fill: parent
        drag.target: dragEnabled ? picker : undefined
        drag.axis: Drag.XAndYAxis
        onClicked: point.clicked()
        onPressAndHold: point.holded()
        onReleased: {
            if (!dragEnabled) return;

            dragged(picker.x, picker.y);
            picker.x = 0;
            picker.y = 0;
        }
    }
}

