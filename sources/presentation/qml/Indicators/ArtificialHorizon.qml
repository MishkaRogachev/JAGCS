import QtQuick 2.6
import QtGraphicalEffects 1.0

import "../Controls"

Item {
    id: root

    property bool available: true
    property bool armed: false

    property bool pitchInverted: true
    property bool rollInverted: false

    property real pitch: 0.0
    property real roll: 0.0

    property real minPitch: -23
    property real maxPitch: 23
    property real pitchStep: 10
    property real minRoll: -35
    property real maxRoll: 35
    property real rollStep: 10

    property real ratio: 1.618

    implicitHeight: width * ratio
    clip: true

    Item {
        id: contents
        anchors.centerIn: parent
        width: parent.width * ratio
        height: width
        visible: false

        Horizon {
            anchors.fill: parent
            effectiveHeight: parent.height
            pitch: pitchInverted ? root.pitch : 0
            roll: rollInverted ? 0 : root.roll
            minPitch: root.minPitch
            maxPitch: root.maxPitch
        }

        PlaneMark {
            anchors.centerIn: parent
            width: parent.width * 0.6
            height: parent.height
            pitch: pitchInverted ? 0 : -root.pitch
            roll: rollInverted ? -root.roll : 0
            markColor: armed ? palette.selectedTextColor : palette.negativeColor
        }

        Label {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -height
            text: qsTr("DISARMED")
            font.pixelSize: root.width * 0.15
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
}
