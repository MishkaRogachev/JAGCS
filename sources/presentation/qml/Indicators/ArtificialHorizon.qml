import QtQuick 2.6
import QtGraphicalEffects 1.0

import "../Controls" as Controls

Item {
    id: root

    property bool operational: false
    property bool armed: false
    property bool guided: false

    property real pitch: 0.0
    property real roll: 0.0
    property real yawspeed: 0.0
    property real desiredPitch: 0.0
    property real desiredRoll: 0.0

    property real minPitch: -23
    property real maxPitch: 23
    property real pitchStep: 10
    property real minRoll: -45
    property real maxRoll: 45
    property real rollStep: 10

    property bool pitchInverted: true
    property bool rollInverted: false
    property alias pitchScaleEnabled: pitchScale.visible

    property alias markWidth: mark.markWidth
    property real ratio: height / width

    clip: true
    implicitHeight: width

    Item {
        id: contents
        anchors.centerIn: parent
        width: parent.height
        height: width
        visible: false

        Horizon {
            id: horizon
            anchors.fill: parent
            effectiveHeight: pitchScale.height
            pitch: pitchInverted ? root.pitch : 0
            roll: rollInverted ? 0 : root.roll
        }

        PitchScale {
            id: pitchScale
            anchors.centerIn: parent
            width: parent.width
            height: parent.height - palette.controlBaseSize * 2
            roll: rollInverted ? 0 : root.roll
            minPitch: pitchInverted ? root.pitch + root.minPitch : root.minPitch
            maxPitch: pitchInverted ? root.pitch + root.maxPitch : root.maxPitch
            pitchStep: root.pitchStep
            opacity: enabled ? 1 : 0.33
            color: operational ? palette.textColor : palette.dangerColor
        }

        DesiredAnglesMark {
            id: desiredMark
            anchors.fill: parent
            effectiveHeight: pitchScale.height
            visible: guided
            pitch: pitchInverted ? root.pitch - desiredPitch : -desiredPitch
            roll: rollInverted ? -desiredRoll : root.roll - desiredRoll
        }

        PlaneMark {
            id: mark
            anchors.fill: parent
            effectiveHeight: pitchScale.height
            pitch: pitchInverted ? 0 : -root.pitch
            roll: rollInverted ? -root.roll : 0
            markColor: armed ? palette.selectedTextColor : palette.dangerColor
        }

        TurnIndicator {
            id: turn
            anchors.fill: parent
            value: yawspeed
        }

        Controls.Label {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -height
            text: qsTr("DISARMED")
            font.pixelSize: root.height * 0.1
            font.bold: true
            color: armed ? "transparent" : palette.dangerColor
        }
    }

    Rectangle {
        id: mask
        anchors.fill: contents
        anchors.margins: 1
        radius: width / 2
    }

    OpacityMask {
        anchors.fill: contents
        source: contents
        maskSource: mask
    }

    RollScale {
        id: rollScale
        anchors.fill: parent
        roll: rollInverted ? -root.roll : root.roll
        minRoll: root.minRoll
        maxRoll: root.maxRoll
        rollStep: root.rollStep
        opacity: enabled ? 1 : 0.33
        color: operational ? palette.textColor : palette.dangerColor
    }
}
