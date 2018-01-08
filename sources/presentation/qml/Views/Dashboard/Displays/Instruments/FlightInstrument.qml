import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: flightDisplay

    property real scalingFactor: 2.7
    property int minSpeed: -settings.value("Gui/fdSpeedStep") * scalingFactor
    property int maxSpeed: settings.value("Gui/fdSpeedStep") * scalingFactor
    property int speedStep: settings.value("Gui/fdSpeedStep")

    property int minAltitude: -settings.value("Gui/fdAltitudeStep") * scalingFactor
    property int maxAltitude: settings.value("Gui/fdAltitudeStep") * scalingFactor
    property int altitudeStep: settings.value("Gui/fdAltitudeStep")

    implicitHeight: width * 0.75

    Indicators.BarIndicator {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: speedLadder.right
        width: speedLadder.majorTickSize + 1
        height: parent.height * 0.7
        value: throttle
    }

    Indicators.Ladder {
        id: speedLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: fd.left
        width: (flightDisplay.width - fd.width) / 2
        height: parent.height * 0.7
        value: displayedIndicatedAirspeed
        error: displayedAirspeedError
        minValue: value + minSpeed
        maxValue: value + maxSpeed
        valueStep: speedStep
        enabled: pitotEnabled
        operational: pitotOperational
        prefix: qsTr("IAS")
        suffix: speedSuffix
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.horizontalCenter: speedLadder.horizontalCenter
        font.pixelSize: speedLadder.fontPixelSize
        digits: 1
        value: displayedGroundSpeed
        enabled: satelliteEnabled
        operational: satelliteOperational
        width: speedLadder.width
        prefix: qsTr("GS")
        suffix: speedSuffix
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: speedLadder.horizontalCenter
        font.pixelSize: speedLadder.fontPixelSize
        digits: 1
        value: displayedTrueAirspeed
        enabled: pitotEnabled
        operational: pitotOperational
        width: speedLadder.width
        prefix: qsTr("TAS")
        suffix: speedSuffix
    }

    Indicators.FlightDirector {
        id: fd
        anchors.centerIn: parent
        height: flightDisplay.height - sizings.padding
        width: flightDisplay.width * 0.55
        enabled: online && ahrsEnabled
        operational: ahrsOperational
        armed: vehicleDisplay.armed
        guided: vehicleDisplay.guided
        pitch: vehicleDisplay.pitch
        roll: vehicleDisplay.roll
        yawspeed: vehicleDisplay.yawspeed
        desiredPitch: vehicleDisplay.desiredPitch
        desiredRoll: vehicleDisplay.desiredRoll
        rollInverted: settings.boolValue("Gui/fdRollInverted")
    }

    Indicators.BarIndicator {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: altitudeLadder.left
        width: altitudeLadder.majorTickSize + 1
        height: parent.height * 0.7
        value: barometricClimb
        fillColor: barometricClimb > 0 ? palette.skyColor : palette.groundColor
        minValue: -10
        maxValue: 10
    }

    Indicators.Ladder {
        id: altitudeLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: fd.right
        width: (flightDisplay.width - fd.width) / 2
        height: parent.height * 0.7
        value: altitudeRelative ? barometricAltitude - homeAltitude : barometricAltitude
        error: altitudeError
        minValue: value + minAltitude
        maxValue: value + maxAltitude
        warningValue: altitudeRelative ? 0 : homeAltitude
        warningColor: palette.groundColor
        valueStep: altitudeStep
        enabled: barometricEnabled
        operational: barometricOperational
        mirrored: true
        prefix: qsTr("ALT")
        suffix: qsTr("m")
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.horizontalCenter: altitudeLadder.horizontalCenter
        font.pixelSize: altitudeLadder.fontPixelSize
        value: satelliteAltitude
        enabled: satelliteEnabled
        operational: satelliteOperational
        width: altitudeLadder.width
        prefix: qsTr("SAT")
        suffix: qsTr("m")
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: altitudeLadder.horizontalCenter
        font.pixelSize: altitudeLadder.fontPixelSize
        value: rangefinderHeight
        digits: 2
        enabled: rangefinderEnabled
        operational: rangefinderOperational
        width: altitudeLadder.width
        prefix: qsTr("RF")
        suffix: qsTr("m")
    }
}
