import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

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
        height: parent.height * 0.6 // TODO: ladder dynamic width calculation
        value: vehicle.powerSystem.throttle
    }

    Indicators.Ladder {
        id: speedLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        height: parent.height * 0.6
        value: vehicle.pitot.present ? vehicle.pitot.displayedIndicatedAirspeed :
                                       vehicle.satellite.displayedGroundSpeed
        error: vehicle.pitot.present ? vehicle.flightControl.displayedAirspeedError : 0
        minValue: value + minSpeed
        maxValue: value + maxSpeed
        valueStep: speedStep
        enabled: vehicle.pitot.present ? vehicle.pitot.enabled : vehicle.satellite.enabled
        operational: vehicle.pitot.present ? vehicle.pitot.operational : vehicle.satellite.operational
        prefix: (vehicle.pitot.present ? qsTr("IAS") : qsTr("GS")) + ", " + vehicle.speedSuffix
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.horizontalCenter: speedLadder.horizontalCenter
        digits: 1
        value: vehicle.satellite.displayedGroundSpeed
        enabled: vehicle.satellite.enabled
        operational: vehicle.satellite.operational
        width: speedLadder.width
        prefix: qsTr("GS") + ", " + vehicle.speedSuffix
        visible: vehicle.pitot.present
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: speedLadder.horizontalCenter
        digits: 1
        value: vehicle.pitot.displayedTrueAirspeed
        enabled: vehicle.pitot.enabled
        operational: vehicle.pitot.operational
        width: speedLadder.width
        prefix: qsTr("TAS") + ", " + vehicle.speedSuffix
        visible: vehicle.pitot.present
    }

    Indicators.AttitudeDirectorIndicator {
        id: fd
        anchors.left: speedLadder.right
        anchors.right: altitudeLadder.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        enabled: vehicle.online && vehicle.ahrs.enabled
        operational: vehicle.ahrs.operational
        armed: vehicle.armed
        guided: vehicle.guided
        pitch: vehicle.ahrs.pitch
        roll: vehicle.ahrs.roll
        yawspeed: vehicle.ahrs.yawspeed
        desiredPitch: vehicle.flightControl.desiredPitch
        desiredRoll: vehicle.flightControl.desiredRoll
        rollInverted: settings.boolValue("Gui/fdRollInverted")
    }

    Indicators.BarIndicator {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: altitudeLadder.left
        width: altitudeLadder.majorTickSize + 1
        height: parent.height * 0.6
        value: vehicle.barometric.climb
        fillColor: vehicle.barometric.climb > 0 ? palette.skyColor : palette.groundColor
        minValue: -10
        maxValue: 10
    }

    Indicators.Ladder {
        id: altitudeLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        height: parent.height * 0.6
        value: vehicle.barometric.displayedAltitude
        error: vehicle.flightControl.altitudeError
        minValue: value + minAltitude
        maxValue: value + maxAltitude
        warningValue: vehicle.altitudeRelative ? 0 : vehicle.homePosition.altitude
        warningColor: palette.groundColor
        valueStep: altitudeStep
        enabled: vehicle.barometric.enabled
        operational: vehicle.barometric.operational
        mirrored: true
        prefix: qsTr("ALT") + ", " + vehicle.altitudeSuffix
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.horizontalCenter: altitudeLadder.horizontalCenter
        value: vehicle.satellite.altitude
        enabled: vehicle.satellite.enabled
        operational: vehicle.satellite.operational
        width: altitudeLadder.width
        prefix: qsTr("SAT") + ", " + vehicle.altitudeSuffix
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: altitudeLadder.horizontalCenter
        value: vehicle.radalt.altitude
        digits: 2
        enabled: vehicle.radalt.enabled
        operational: vehicle.radalt.operational
        visible: vehicle.radalt.present
        width: altitudeLadder.width
        prefix: qsTr("RAD") + ", " + vehicle.altitudeSuffix
    }
}
