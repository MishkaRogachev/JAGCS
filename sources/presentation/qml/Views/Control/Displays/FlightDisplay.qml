import QtQuick 2.6

import "qrc:/JS/helper.js" as Helper
import "qrc:/Indicators" as Indicators

BaseDisplay {
    id: root

    property bool ahrsEnabled: false
    property bool ahrsOperational: false
    property alias pitch: ai.pitch
    property alias roll: ai.roll
    property alias desiredPitch: ai.desiredPitch
    property alias desiredRoll: ai.desiredRoll
    property alias yawspeed: ai.yawspeed
    property alias armed: ai.armed
    property alias guided: ai.guided

    property int throttle: 0

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property real groundspeed: 0
    property int satelliteAltitude: 0

    property bool pitotEnabled: false
    property bool pitotOperational: false
    property real indicatedAirspeed: 0
    property real trueAirspeed: 0

    property bool barometricEnabled: false
    property bool barometricOperational: false
    property int barometricAltitude: 0
    property real barometricClimb: 0

    property bool rangefinderEnabled: false
    property bool rangefinderOperational: false
    property real rangefinderHeight: 0

    property int homeAltitude: 0

    property real scalingFactor: 2.7
    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int minSpeed: -settings.value("Gui/fdSpeedStep") * scalingFactor
    property int maxSpeed: settings.value("Gui/fdSpeedStep") * scalingFactor
    property int speedStep: settings.value("Gui/fdSpeedStep")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")

    property int minAltitude: -settings.value("Gui/fdAltitudeStep") * scalingFactor
    property int maxAltitude: settings.value("Gui/fdAltitudeStep") * scalingFactor
    property int altitudeStep: settings.value("Gui/fdAltitudeStep")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    implicitWidth: ai.width / 0.55
    minimumHeight: palette.controlBaseSize * 4
    maximumHeight: palette.controlBaseSize * 7

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
        anchors.right: ai.left
        width: (root.width - ai.width) / 2
        height: parent.height * 0.7
        value: {
            switch (speedUnits) {
            default:
            case 0: return indicatedAirspeed;
            case 1: return Helper.mpsToKph(indicatedAirspeed);
            }
        }
        minValue: value + minSpeed
        maxValue: value + maxSpeed
        valueStep: speedStep
        enabled: pitotEnabled
        operational: pitotOperational
        prefix: qsTr("IAS")
        suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        digits: 1
        value: {
            switch (speedUnits) {
            default:
            case 0: return groundspeed;
            case 1: return Helper.mpsToKph(groundspeed);
            }
        }
        enabled: satelliteEnabled
        operational: satelliteOperational
        width: speedLadder.width
        prefix: qsTr("GS")
        suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        digits: 1
        value: {
            switch (speedUnits) {
            default:
            case 0: return trueAirspeed;
            case 1: return Helper.mpsToKph(trueAirspeed);
            }
        }
        enabled: pitotEnabled
        operational: pitotOperational
        width: speedLadder.width
        prefix: qsTr("TAS")
        suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
    }

    Indicators.ArtificialHorizon {
        id: ai
        anchors.centerIn: parent
        height: root.height - palette.padding
        width: root.width * 0.55
        enabled: ahrsEnabled
        operational: ahrsOperational
        rollInverted: root.rollInverted
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
        anchors.left: ai.right
        width: (root.width - ai.width) / 2
        height: parent.height * 0.7
        value: altitudeRelative ? barometricAltitude - homeAltitude : barometricAltitude
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
        anchors.right: parent.right
        value: satelliteAltitude
        enabled: satelliteEnabled
        operational: satelliteOperational
        width: altitudeLadder.width
        prefix: qsTr("SAT")
        suffix: qsTr("m")
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        value: rangefinderHeight
        digits: 2
        enabled: rangefinderEnabled
        operational: rangefinderOperational
        width: altitudeLadder.width
        prefix: qsTr("RF")
        suffix: qsTr("m")
    }
}
