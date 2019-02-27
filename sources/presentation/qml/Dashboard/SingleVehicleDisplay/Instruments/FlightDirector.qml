import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

BaseInstrument {
    id: root

    property real scalingFactor: 2.7
    property int minSpeed: -dashboard.speedStep * scalingFactor
    property int maxSpeed: dashboard.speedStep * scalingFactor

    property int minAltitude: -dashboard.altitudeStep * scalingFactor
    property int maxAltitude: dashboard.altitudeStep * scalingFactor

    Connections {
        target: display
        onUpdateCommandStatus: {
            switch (command) {
            case spdPicker.command:
                spdPicker.status = status;
                break;
            case altPicker.command:
                altPicker.status = status;
                break;
            default:
                break;
            }
        }
    }

    implicitHeight: width * 0.75

    Indicators.AttitudeDirectorIndicator {
        id: fd
        anchors.left: throttleBar.right
        anchors.right: climbBar.left
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
        enabled: vehicle.online && vehicle.ahrs.enabled
        operational: vehicle.ahrs.operational
        armed: vehicle.armed
        pitch: vehicle.ahrs.pitch
        roll: vehicle.ahrs.roll
        yawspeed: vehicle.ahrs.yawspeed
        desiredVisible: vehicle.stab
        desiredPitch: vehicle.flightControl.desiredPitch
        desiredRoll: vehicle.flightControl.desiredRoll
        rollInverted: dashboard.rollInverted
        inputEnabled: manual.enabled
        onAddPitch: manual.addImpact(ManualController.Pitch, value)
        onAddRoll: manual.addImpact(ManualController.Roll, value)
    }

    Indicators.BarIndicator {
        id: throttleBar
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: speedLadder.right
        width: speedLadder.minorTickSize
        height: fd.sideHeight
        value: vehicle.powerSystem.throttle
    }

    Indicators.BarIndicator {
        id: climbBar
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: altitudeLadder.left
        width: altitudeLadder.minorTickSize
        height: fd.sideHeight
        value: vehicle.barometric.climb
        fillColor: vehicle.barometric.climb > 0 ? Indicators.Theme.skyColor : Indicators.Theme.groundColor
        minValue: -10
        maxValue: 10
    }

    Indicators.Ladder {
        id: speedLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        height: fd.sideHeight
        value: units.convertSpeedTo(speedUnits, vehicle.pitot.present ?
                                        vehicle.pitot.indicatedAirspeed :
                                        vehicle.satellite.groundspeed)
        minValue: value + minSpeed
        maxValue: value + maxSpeed
        valueStep: speedStep
        enabled: vehicle.pitot.present ? vehicle.pitot.enabled : vehicle.satellite.enabled
        operational: vehicle.pitot.present ? vehicle.pitot.operational : vehicle.satellite.operational
        prefix: (vehicle.pitot.present ? qsTr("IAS") : qsTr("GS")) + ", " + speedSuffix

        Indicators.LadderMark {
            id: spdMark
            anchors.fill: parent
            visible: vehicle.guided && vehicle.pitot.present
            color: spdPicker.color
            value: parent.value + units.convertSpeedTo(speedUnits,
                                                       vehicle.flightControl.airspeedError)
        }

        Indicators.LadderPicker {
            id: spdPicker
            anchors.fill: parent
            enabled: (vehicle.mode === Domain.Mission || vehicle.mode === Domain.NavTo) &&
                     !manual.enabled
            command: vehicle.pitot.present ? Command.SetAirspeed : Command.SetGroundspeed
            args: [ units.convertSpeedFrom(speedUnits, inputValue) ]
            value: spdMark.value
        }

        Indicators.LadderButtons {
            anchors.fill: parent
            inputEnabled: manual.enabled
            onAddValue: manual.addImpact(ManualController.Throttle, value)
        }
    }

    Indicators.Ladder {
        id: altitudeLadder
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        height: fd.sideHeight
        value: units.convertDistanceTo(altitudeUnits, vehicle.barometric.displayedAltitude)
        minValue: value + minAltitude
        maxValue: value + maxAltitude
        warningValue: altitudeRelative ?
                          0 : units.convertDistanceTo(altitudeUnits, vehicle.homeAltitude)
        warningColor: Indicators.Theme.groundColor
        valueStep: dashboard.altitudeStep
        enabled: vehicle.barometric.enabled
        operational: vehicle.barometric.operational
        mirrored: true
        prefix: qsTr("ALT") + ", " + altitudeSuffix

        Indicators.LadderMark {
            id: altMark
            anchors.fill: parent
            visible: vehicle.guided
            color: altPicker.color
            value: parent.value +
                   units.convertDistanceTo(altitudeUnits, vehicle.flightControl.altitudeError)
        }

        Indicators.LadderPicker {
            id: altPicker
            anchors.fill: parent
            enabled:  vehicle.mode === Domain.Circle ||
                      vehicle.mode === Domain.Loiter ||
                      vehicle.mode === Domain.NavTo ||
                      vehicle.mode === Domain.Mission ||
                      vehicle.mode === Domain.Return
            command: Command.SetAltitude
            args: [ vehicle.barometric.fromDisplayedAltitude(
                    units.convertDistanceFrom(altitudeUnits, inputValue)) ]
            value: altMark.value
        }
    }

    Indicators.ValueLabel {
        anchors.top: parent.top
        anchors.horizontalCenter: speedLadder.horizontalCenter
        digits: 1
        value: units.convertSpeedTo(speedUnits, vehicle.satellite.groundspeed)
        enabled: vehicle.satellite.enabled
        visible: vehicle.pitot.present
        operational: vehicle.satellite.operational
        width: speedLadder.width
        prefix: qsTr("GS") + ", " + speedSuffix
    }

    Indicators.ValueLabel {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: speedLadder.horizontalCenter
        digits: 1
        value: units.convertSpeedTo(speedUnits, vehicle.pitot.trueAirspeed)
        enabled: vehicle.pitot.enabled
        operational: vehicle.pitot.operational
        width: speedLadder.width
        prefix: qsTr("TAS") + ", " + speedSuffix
        visible: vehicle.pitot.present
    }

    Indicators.ValueLabel {
        anchors.top: parent.top
        anchors.horizontalCenter: altitudeLadder.horizontalCenter
        anchors.horizontalCenterOffset: -itemMenuButton.width / 2
        value: units.convertDistanceTo(altitudeUnits, vehicle.satellite.altitude)
        enabled: vehicle.satellite.enabled
        operational: vehicle.satellite.operational
        visible: vehicle.satellite.present
        width: altitudeLadder.width
        prefix: qsTr("SAT") + ", " + altitudeSuffix
    }

    Indicators.ValueLabel {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: altitudeLadder.horizontalCenter
        value: units.convertDistanceTo(altitudeUnits, vehicle.radalt.altitude)
        digits: 2
        enabled: vehicle.radalt.enabled
        operational: vehicle.radalt.operational
        visible: vehicle.radalt.present
        width: altitudeLadder.width
        prefix: qsTr("RAD") + ", " + altitudeSuffix
    }
}
