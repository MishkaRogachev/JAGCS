import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Indicators" as Indicators

BaseDisplay {
    id: navigationDisplay

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
    property real groundspeed: 0
    property int targetDistance: 0
    property int homeDistance: 0
    property real homeDirection: 0
    property real windDirection: 0
    property real windSpeed: 0

    property url vehicleMark: "qrc:/indicators/fixed_wing_mark.svg" // TODO: vehicle mark

    property int speedUnits: settings.value("Gui/fdSpeedUnits")

    implicitHeight: width * 0.75

    NavigationDisplayPresenter {
        id: presenter
        view: navigationDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    Indicators.DistanceLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        font.pixelSize: Math.max(hsi.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("DIST")
        color: guided ? palette.activeMissionColor : palette.textColor
        opacity: guided ? 1 : 0.33
        distance: targetDistance
        width: parent.width * 0.2
    }

    Indicators.DistanceLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        font.pixelSize: Math.max(hsi.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("HOME")
        distance: homeDistance
        width: parent.width * 0.2
        enabled: homeDistance > 0
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.2
        font.pixelSize: Math.max(hsi.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("WIND")
        value: {
            switch (speedUnits) {
            default:
            case 0: return windSpeed;
            case 1: return Helper.mpsToKph(windSpeed);
            }
        }
        suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
        enabled: windSpeed > 0
    }

    Indicators.SituationIndicator {
        id: hsi
        anchors.centerIn: parent
        height: Math.min(parent.height, parent.width * 0.6) - sizings.padding
        width: height
        mark: vehicleMark
        opacity: compassEnabled ? 1 : 0.33
        color: compassOperational ? palette.textColor : palette.dangerColor
        courseEnabled: groundspeed > 0.1
        courseColor: satelliteEnabled ? (satelliteOperational ? palette.positiveColor :
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
        color: guided ? palette.activeMissionColor : palette.textColor
        opacity: guided ? 1 : 0.33
        value: targetBearing
        width: parent.width * 0.2
        font.pixelSize: Math.max(hsi.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("TRG")
        suffix: "\u00B0"
    }

    Indicators.FdLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        value: heading
        width: parent.width * 0.2
        enabled: compassEnabled
        operational: compassOperational
        font.pixelSize: Math.max(hsi.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("HDG")
        suffix: "\u00B0"
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        value: course
        width: parent.width * 0.2
        enabled: compassEnabled
        operational: compassOperational
        font.pixelSize: Math.max(hsi.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("CRS")
        suffix: "\u00B0"
    }
}
