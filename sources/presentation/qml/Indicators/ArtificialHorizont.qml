import QtQuick 2.6
import QtGraphicalEffects 1.0

Item {
    id: root

    property int pitch: 0.0
    property int roll: 0.0
    property int velocity: 0.0
    property int altitude: 0.0

    property bool pitchInverted: true
    property bool rollInverted: true
    property bool insAvalible: true
    property bool altitudeAvalible: true
    property bool velocityAvalible: true

    property int minVelocity: -13
    property int maxVelocity: 13
    property int velocityStep: 5
    property int minPitch: -23
    property int maxPitch: 23
    property int pitchStep: 10
    property int minRoll: -35
    property int maxRoll: 35
    property int rollStep: 10
    property int minAltitude: -27
    property int maxAltitude: 27
    property int altitudeStep: 10

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }
    Behavior on velocity { PropertyAnimation { duration: 100 } }
    Behavior on altitude { PropertyAnimation { duration: 100 } }

    height: width

    Item {
        id: pitchRollContents
        anchors.fill: parent
        visible: false

        Horizont {
            id: horizont
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
            fontPixelSize: palette.fontPixelSize * 0.8
            height: parent.height - palette.controlBaseSize * 2
            pitch: pitchInverted ? root.pitch : 0
            roll: rollInverted ? 0 : root.roll
            minPitch: root.pitch + root.minPitch
            maxPitch: root.pitch + root.maxPitch
            pitchStep: root.pitchStep
            opacity: insAvalible ? 1 : 0.33
        }

        PlaneMark {
            anchors.centerIn: parent
            width: parent.width * 0.6
            height: pitchScale.height
            pitch: pitchInverted ? 0 : -root.pitch
            roll: rollInverted ? -root.roll : 0
        }
    }

    Rectangle {
        id: mask
        anchors.fill: parent
        anchors.margins: -4
        radius: width / 2
        border.color: palette.sunkenColor
        border.width: 8
    }

    OpacityMask {
        anchors.fill: parent
        source: pitchRollContents
        maskSource: mask
    }

    RollScale {
        id: rollScale
        anchors.fill: parent
        fontPixelSize: palette.fontPixelSize
        roll: rollInverted ? -root.roll : root.roll
        minRoll: root.minRoll
        maxRoll: root.maxRoll
        rollStep: root.rollStep
        opacity: insAvalible ? 1 : 0.33
    }

    LinearScale {
        id: velocityScale
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: parent.width * 0.2
        height: parent.height * 0.8
        value: root.velocity
        minValue: velocity + minVelocity
        maxValue: velocity + maxVelocity
        valueStep: velocityStep
        scaleColor: velocityAvalible ? palette.textColor : palette.disabledColor
        canvasRotation: 90
        fontPixelSize: palette.fontPixelSize * 0.8
    }

    LinearScale {
        id: altitudeScale
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        width: parent.width * 0.2
        height: parent.height * 0.8
        value: root.altitude
        minValue: altitude + minAltitude
        maxValue: altitude + maxAltitude
        valueStep: altitudeStep
        scaleColor: altitudeAvalible ? palette.textColor : palette.disabledColor
        canvasRotation: -90
        fontPixelSize: palette.fontPixelSize * 0.8
    }
}
