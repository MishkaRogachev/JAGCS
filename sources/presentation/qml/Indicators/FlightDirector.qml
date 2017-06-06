import QtQuick 2.6
import QtGraphicalEffects 1.0

import "../Controls" as Controls

ArtificialHorizon {
    id: root

    property int speed: 0.0
    property int altitude: 0.0
    property int throttle: 0
    property int climb: 0

    property string speedPrefix
    property string altitudePrefix

    property bool speedAvalible: true
    property bool altitudeAvalible: true

    property int minSpeed: -13
    property int maxSpeed: 13
    property int speedStep: 5
    property int minAltitude: -27
    property int maxAltitude: 27
    property int altitudeStep: 10
    property int minThrottle: 0
    property int maxThrottle: 100
    property int minClimb: -12
    property int maxClimb: 12

    ratio: 1

    RollScale {
        id: rollScale
        anchors.fill: parent
        roll: rollInverted ? -root.roll : root.roll
        minRoll: root.minRoll
        maxRoll: root.maxRoll
        rollStep: root.rollStep
    }

    BarIndicator {
        id: throttleBar
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.03
        height: parent.height * 0.8
        value: throttle
        fillColor: palette.selectionColor
        minValue: minThrottle
        maxValue: maxThrottle
    }

    Ladder {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: throttleBar.right
        width: parent.width * 0.17
        height: parent.height * 0.8
        value: speed
        minValue: speed + minSpeed
        maxValue: speed + maxSpeed
        valueStep: speedStep
        color: speedAvalible ? palette.textColor : palette.disabledColor
        canvasRotation: 90
        prefix: speedPrefix
    }

    Ladder {
        id: altitudeLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: climbScale.left
        width: parent.width * 0.17
        height: parent.height * 0.8
        value: altitude
        minValue: altitude + minAltitude
        maxValue: altitude + maxAltitude
        valueStep: altitudeStep
        color: altitudeAvalible ? palette.textColor : palette.disabledColor
        canvasRotation: -90
        prefix: altitudePrefix
    }

    BarIndicator {
        id: climbScale
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        width: root.width * 0.03
        height: root.height * 0.8
        value: climb
        fillColor: {
            if (!altitudeAvalible) return palette.disabledColor;
            if (value > 0) return palette.skyColor;
            if (value > minValue) return palette.groundColor;
            return palette.negativeColor;
        }
        minValue: minClimb
        maxValue: maxClimb
    }
}
