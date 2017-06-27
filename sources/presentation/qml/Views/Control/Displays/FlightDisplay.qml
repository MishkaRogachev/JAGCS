import QtQuick 2.6

import "qrc:/Indicators" as Indicators

Item {
    id: root

    property alias pitch: af.pitch
    property alias roll: af.roll
    property alias armed: af.armed

    property int throttle: 0

    property real groundspeed: 0
    property real indicatedAirspeed: 0
    property real trueAirspeed: 0

    property int satelliteAltitude: 0
    property int barometricAltitude: 0
    property real barometricClimb: 0
    property int rangefinderHeight: 0

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property bool airSpeedAvalible: true
    property bool altitudeAvalible: true

    property int minSpeed: -13
    property int maxSpeed: 13
    property int speedStep: 5

    property int minAltitude: -27
    property int maxAltitude: 27
    property int altitudeStep: 10

    implicitHeight: af.height

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("GS")
        digits: 1
        value: groundspeed
        color: satelliteEnabled ? satelliteOperational ? palette.textColor :
                                                         palette.negativeColor :
                                                         palette.disabledColor
        width: speedLadder.width
    }

    Indicators.BarIndicator {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: parent.width * 0.03
        height: parent.height * 0.7
        value: throttle
    }

    Indicators.Ladder {
        id: speedLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        width: parent.width * 0.2
        height: parent.height * 0.7
        value: indicatedAirspeed
        minValue: indicatedAirspeed + minSpeed
        maxValue: indicatedAirspeed + maxSpeed
        valueStep: speedStep
        color: airSpeedAvalible ? palette.textColor : palette.disabledColor
        canvasRotation: 90
        prefix: qsTr("IAS")
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        prefix: qsTr("TAS")
        digits: 1
        value: trueAirspeed
        width: speedLadder.width
    }

    Indicators.ArtificialHorizon {
        id: af
        anchors.centerIn: parent
        width: parent.width * 0.58
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.right: parent.right
        prefix: qsTr("SAT")
        color: satelliteEnabled ? satelliteOperational ? palette.textColor :
                                                         palette.negativeColor :
                                                         palette.disabledColor
        value: satelliteAltitude
        width: altitudeLadder.width
    }

    Indicators.Ladder {
        id: altitudeLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        width: parent.width * 0.2
        height: parent.height * 0.7
        value: barometricAltitude
        minValue: barometricAltitude + minAltitude
        maxValue: barometricAltitude + maxAltitude
        valueStep: altitudeStep
        color: altitudeAvalible ? palette.textColor : palette.disabledColor
        canvasRotation: -90
        prefix: qsTr("ALT")
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        prefix: qsTr("RF")
        value: rangefinderHeight
        width: altitudeLadder.width
    }
}
