import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: ai

    property bool operational: false
    property bool available: false

    property real pitch: 0.0
    property real roll: 0.0

    property real maxPitch: 23
    property real minPitch: -maxPitch

    property bool pitchInverted: true
    property bool rollInverted: false

    property real ratio: height / width
    property real effectiveHeight: height - sizings.controlBaseSize * 2

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
        pitch: pitchInverted ? ai.pitch : 0
        roll: rollInverted ? 0 : ai.roll
        minPitch: ai.minPitch
        maxPitch: ai.maxPitch
        operational: ai.operational
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
