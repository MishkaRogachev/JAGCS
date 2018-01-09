import QtQuick 2.6
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    // TODO: to common
    property url vehicleMark: {
        switch (vehicleType) {
        case Vehicle.FixedWing:
            return "qrc:/indicators/fixed_wing_mark.svg"
        case Vehicle.FlyingWing:
            return "qrc:/indicators/flying_wing_mark.svg"
        case Vehicle.Tricopter:
        case Vehicle.Quadcopter:
        case Vehicle.Hexcopter:
            return "qrc:/indicators/quadcopter_mark.svg"
        case Vehicle.Helicopter:
        case Vehicle.Coaxial:
            return "qrc:/indicators/helicopter_mark.svg"
        default:
            return "qrc:/indicators/unknown_mark.svg"
        }
    }

    implicitHeight: width * 0.75

    Indicators.DistanceLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("DIST")
        color: guided ? palette.activeMissionColor : palette.textColor
        opacity: guided ? 1 : 0.33
        distance: targetDistance
        width: parent.width * 0.2
    }

    Indicators.DistanceLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("HOME")
        distance: homeDistance
        width: parent.width * 0.2
        enabled: homeDistance > 0
    }

    Indicators.FdLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.2
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("WIND")
        value: displayedWindSpeed
        suffix: speedSuffix
        enabled: windSpeed > 0
    }

    Indicators.Compass {
        id: compass
        anchors.centerIn: parent
        height: Math.min(parent.height, parent.width * 0.6) - sizings.padding
        width: height
        mark: vehicleMark
        heading: vehicleDisplay.heading
        course: vehicleDisplay.course
        courseEnabled: groundspeed > 0.1
        opacity: compassEnabled ? 1 : 0.33
        headingColor: compassOperational ? palette.textColor : palette.dangerColor
        courseColor: satelliteEnabled ? (satelliteOperational ? palette.positiveColor :
                                                                palette.dangerColor) :
                                        "transparent"

        Indicators.SituationIndicator {
            id: hsi
            anchors.fill: parent
            guided: vehicleDisplay.guided
            targetBearing: vehicleDisplay.targetBearing
            desiredHeading: vehicleDisplay.desiredHeading
            trackError: vehicleDisplay.trackError
            z: -1
        }

        Item {
            anchors.fill: parent
            rotation: homeDirection - heading
            visible: homeDistance > 0
            z: -1

            Image {
                width: parent.width * 0.12
                height: width
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -(compass.textOffset + compass.majorTickOffset)
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
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
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
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
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
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("CRS")
        suffix: "\u00B0"
    }
}
