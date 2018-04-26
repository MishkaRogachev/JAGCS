import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: ai

    property real pitch: 0.0
    property real roll: 0.0

    property real maxPitch: 23
    property real minPitch: -maxPitch

    property bool pitchInverted: true
    property bool rollInverted: false

    property real effectiveHeight: height
    readonly property real sideHeight: Math.sqrt(Math.pow(height, 2) - Math.pow(width, 2))

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }

    clip: true
    implicitHeight: width

    Horizon {
        id: horizon
        anchors.centerIn: parent
        width: parent.height
        height: width
        visible: false
        effectiveHeight: ai.effectiveHeight
        pitch: pitchInverted && !isNaN(ai.pitch) ? ai.pitch : 0
        roll: !rollInverted && !isNaN(ai.roll) ? ai.roll : 0
        minPitch: ai.minPitch
        maxPitch: ai.maxPitch
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
}
