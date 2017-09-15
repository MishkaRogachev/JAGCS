import QtQuick 2.6

import "qrc:/Indicators" as Indicators

BaseDisplay {
    id: root

    property alias guided: hsi.guided
    property alias heading: hsi.heading
    property alias course: hsi.course
    property alias targetBearing: hsi.targetBearing
    property alias desiredHeading: hsi.desiredHeading
    property alias trackError: hsi.trackError

    property bool compassEnabled: false
    property bool compassOperational: false
    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property int targetDistance: 0
    property int homeDistance: 0
    property real homeDirection: 0
    property real windDirection: 0
    property real windSpeed: 0

    property int speedUnits: settings.value("Gui/fdSpeedUnits")

    minimumHeight: palette.controlBaseSize * 3
    maximumHeight: palette.controlBaseSize * 6

    Indicators.DistanceLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("DIST")
        color: guided ? palette.activeMissionColor : palette.textColor
        opacity: guided ? 1 : 0.33
        distance: targetDistance
        width: parent.width * 0.2
    }

    Indicators.DistanceLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        prefix: qsTr("HOME")
        distance: homeDistance
        width: parent.width * 0.2
        enabled: homeDistance > 0
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.2
        prefix: qsTr("WIND")
        value: {
            switch (speedUnits) {
            default:
            case 0: return windSpeed;
            case 1: return Helper.mpsToKph(windSpeed);
            }
        }
        enabled: windSpeed > 0
    }

    Indicators.SituationIndicator {
        id: hsi
        anchors.centerIn: parent
        height: Math.min(parent.height, parent.width * 0.6) - palette.padding
        width: height
        mark: vehicleMark
        opacity: compassEnabled ? 1 : 0.33
        color: compassOperational ? palette.textColor : palette.dangerColor
        courseColor: satelliteEnabled ? (satelliteOperational ? palette.missionColor :
                                                                palette.dangerColor) :
                                        "transparent"

        Item {
            anchors.fill: parent
            rotation: homeDirection - heading
            visible: homeDistance > 0
            z: -1

            Image {
                width: parent.width * 0.12
                height: width
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -parent.height * 0.3
                source: "qrc:/icons/home.svg"
                rotation: -parent.rotation
            }
        }

        // TODO: wind indicator
    }

    Indicators.FdLabel {
        anchors.top: parent.top
        anchors.right: parent.right
        prefix: qsTr("TRG")
        color: guided ? palette.activeMissionColor : palette.textColor
        opacity: guided ? 1 : 0.33
        value: targetBearing
        width: parent.width * 0.2
    }

    Indicators.FdLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        prefix: qsTr("HDG")
        value: heading
        width: parent.width * 0.2
        enabled: compassEnabled
        operational: compassOperational
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        prefix: qsTr("CRS")
        value: course
        width: parent.width * 0.2
        enabled: compassEnabled
        operational: compassOperational
    }
}
