import QtQuick 2.6
import QtGraphicalEffects 1.0

Column {
    id: root

    property int pitch: 0.0
    property int roll: 0.0
    property int yaw: 0.0
    property int velocity: 0.0
    property int altitude: 0.0

    property bool pitchInverted: true
    property bool rollInverted: true
    property int rollOffset: 28

    property int minVelocity: -13
    property int maxVelocity: 13
    property int velocityStep: 5
    property int minPitch: -23
    property int maxPitch: 23
    property int minRoll: -45
    property int maxRoll: 45
    property int minAltitude: -27
    property int maxAltitude: 27
    property int altitudeStep: 10
    property int minYaw: -17
    property int maxYaw: 17

    Behavior on pitch { PropertyAnimation { duration: 100 } }
    Behavior on roll { PropertyAnimation { duration: 100 } }
    Behavior on yaw { PropertyAnimation { duration: 100 } }
    Behavior on velocity { PropertyAnimation { duration: 100 } }
    Behavior on altitude { PropertyAnimation { duration: 100 } }

    Row {
        id: row
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: root.spacing

        LinearScale {
            id: velocityScale
            value: root.velocity
            minValue: velocity + minVelocity
            maxValue: velocity + maxVelocity
            valueStep: velocityStep
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height + rollOffset
            canvasRotation: 90
        }

        Item {
            id: picthRoll
            anchors.verticalCenter: parent.verticalCenter
            width: root.width - velocityScale.width -
                   altitudeScale.width - row.spacing * 2
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
                    height: parent.height - rollOffset - 48 // roll mark
                    pitch: pitchInverted ? root.pitch : 0
                    roll: rollInverted ? 0 : root.roll
                    minPitch: root.pitch + root.minPitch
                    maxPitch: root.pitch + root.maxPitch
                }

                PlaneMark {
                    anchors.centerIn: parent
                    width: parent.width
                    height: pitchScale.height
                    pitch: pitchInverted ? 0 : -root.pitch
                    roll: rollInverted ? -root.roll : 0
                }
            }

            OpacityMask {
                anchors.fill: parent
                source: pitchRollContents
                maskSource: mask
            }

            Rectangle {
                id: mask
                width: parent.width
                height: parent.height
                radius: width / 2
                visible: false
            }

            RollScale {
                id: rollScale
                anchors.centerIn: parent
                height: parent.height + rollOffset
                offset: rollOffset / 2
                roll: rollInverted ? 0 : root.roll
                rollValue: root.roll
                minRoll: root.minRoll
                maxRoll: root.maxRoll
            }
        }

        LinearScale {
            id: altitudeScale
            value: root.altitude
            minValue: altitude + minAltitude
            maxValue: altitude + maxAltitude
            valueStep: altitudeStep
            anchors.verticalCenter: parent.verticalCenter
            height: picthRoll.height + rollOffset
            canvasRotation: -90
        }
    }

    LinearScale {
        id: yawScale
        value: yaw
        minValue: yaw + minYaw
        maxValue: yaw + maxYaw
        valueStep: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: root.width - 16
    }
}
