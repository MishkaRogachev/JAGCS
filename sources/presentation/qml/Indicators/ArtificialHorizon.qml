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

    property real minPitch: -maxPitch
    property real maxPitch: 23
    property real pitchStep: 5
    property real minRoll: -maxRoll
    property real maxRoll: width > height ? 90 : 90 - (180 * Math.acos(width / height) / Math.PI)
    property real rollStep: 10

    property bool pitchInverted: true
    property bool rollInverted: false
    property alias pitchScaleEnabled: pitchScale.visible

    property alias markWidth: mark.markWidth
    property real ratio: height / width

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }
    Behavior on yawspeed { PropertyAnimation { duration: 100 } }
    Behavior on desiredPitch { PropertyAnimation { duration: 100 } }
    Behavior on desiredRoll { PropertyAnimation { duration: 100 } }

    clip: true
    implicitHeight: width

    Horizon {
        id: horizon
        anchors.centerIn: parent
        width: parent.height
        height: width
        visible: false
        effectiveHeight: pitchScale.height
        pitch: pitchInverted ? root.pitch : 0
        roll: rollInverted ? 0 : root.roll
    }

    Rectangle {
        id: mask
        anchors.fill: horizon
        anchors.margins: 1
        radius: width / 2
    }

    OpacityMask {
        anchors.fill: horizon
        source: horizon
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
        anchors.margins: palette.margins
        effectiveHeight: pitchScale.height
        visible: guided
        pitch: pitchInverted ? root.pitch - desiredPitch : -desiredPitch
        roll: rollInverted ? -desiredRoll : root.roll - desiredRoll
    }

    TurnIndicator {
        id: turn
        anchors.fill: parent
        value: yawspeed
    }

    PlaneMark {
        id: mark
        anchors.fill: parent
        anchors.margins: palette.margins
        effectiveHeight: pitchScale.height
        pitch: pitchInverted ? 0 : -root.pitch
        roll: rollInverted ? -root.roll : 0
        markColor: armed ? palette.selectedTextColor : palette.dangerColor
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
