import QtQuick 2.6
import QtGraphicalEffects 1.0

import "../Controls" as Controls

Item {
    id: root

    property bool operational: false
    property bool armed: false

    property real pitch: 0.0
    property real roll: 0.0
    property real yawspeed: 0.0

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
    property real ratio: 1.4

    implicitHeight: width * ratio
    clip: true

    Item {
        id: contents
        anchors.centerIn: parent
        width: parent.width * ratio
        height: width
        visible: false

        Horizon {
            id: horizon
            anchors.fill: parent
            effectiveHeight: pitchScale.height
            pitch: pitchInverted ? root.pitch : 0
            roll: rollInverted ? 0 : root.roll
            minPitch: root.minPitch
            maxPitch: root.maxPitch
        }

        PitchScale {
            id: pitchScale
            anchors.centerIn: parent
            width: parent.width
            height: parent.height - palette.controlBaseSize * 2
            pitch: pitchInverted ? root.pitch : 0
            roll: rollInverted ? 0 : root.roll
            minPitch: root.pitch + root.minPitch
            maxPitch: root.pitch + root.maxPitch
            pitchStep: root.pitchStep
            color: enabled ? (operational ? palette.textColor : palette.negativeColor) :
                             palette.disabledColor
        }

        PlaneMark {
            id: mark
            anchors.centerIn: parent
            width: parent.width * 0.6
            height: parent.height
            pitch: pitchInverted ? 0 : -root.pitch
            roll: rollInverted ? -root.roll : 0
            markColor: armed ? palette.selectedTextColor : palette.negativeColor
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
            color: armed ? "transparent" : palette.negativeColor
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
        color: enabled ? (operational ? palette.textColor : palette.negativeColor) :
                         palette.disabledColor
    }
}
