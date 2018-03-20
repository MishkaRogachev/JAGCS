import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    implicitHeight: width * 0.6

    Indicators.DistanceLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("DIST")
        color: vehicle.guided ? palette.activeMissionColor : palette.textColor
        opacity: vehicle.guided ? 1 : 0.33
        distance: vehicle.navigator.targetDistance
        width: parent.width * 0.2
    }

    Indicators.DistanceLabel {
        id: homeLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("HOME")
        distance: vehicle.position.distanceTo(vehicle.homePosition)
        width: parent.width * 0.2
        enabled: distance > 0
    }

    Indicators.InstrumentLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.2
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("WIND")
        value: units.convertSpeedTo(dashboard.speedUnits, vehicle.wind.speed)
        suffix: dashboard.speedSuffix
        enabled: value > 0
    }

    Indicators.Compass {
        id: compass
        anchors.centerIn: parent
        height: parent.height - sizings.padding
        width: height
        mark: translator.imageFromVehicleType(vehicle.vehicleType)
        heading: vehicle.compass.heading
        course: vehicle.satellite.course
        courseEnabled: vehicle.satellite.groundSpeed > 0.1
        opacity: vehicle.compass.enabled ? 1 : 0.33
        headingColor: vehicle.compass.operational ? palette.textColor : palette.dangerColor
        courseColor: vehicle.satellite.enabled ?
                         (vehicle.satellite.operational ?
                              palette.positiveColor : palette.dangerColor) : "transparent"

        Indicators.SituationIndicator {
            id: hsi
            anchors.fill: parent
            guided: vehicle.guided
            heading: vehicle.compass.heading
            targetBearing: vehicle.navigator.targetBearing
            desiredHeading: vehicle.flightControl.desiredHeading
            trackError: vehicle.navigator.trackError
            z: -1
        }

        Item {
            anchors.fill: parent
            rotation: vehicle.position.azimuthTo(vehicle.homePosition) - vehicle.compass.heading
            visible: homeLabel.distance > 0
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
    }

    Indicators.InstrumentLabel {
        anchors.top: parent.top
        anchors.right: parent.right
        color: vehicle.guided ? palette.activeMissionColor : palette.textColor
        opacity: vehicle.guided ? 1 : 0.33
        value: vehicle.navigator.targetBearing
        width: parent.width * 0.2
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("TRG")
        suffix: "\u00B0"
    }

    Indicators.InstrumentLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        value: vehicle.compass.heading
        width: parent.width * 0.2
        enabled: vehicle.compass.enabled
        operational: vehicle.compass.operational
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("HDG")
        suffix: "\u00B0"
    }

    Indicators.InstrumentLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        value: vehicle.satellite.course
        width: parent.width * 0.2
        enabled: vehicle.satellite.enabled
        operational: vehicle.satellite.operational
        font.pixelSize: Math.max(compass.height * 0.08, sizings.fontPixelSize * 0.5)
        prefix: qsTr("CRS")
        suffix: "\u00B0"
    }

    Controls.Button {
        anchors.top: parent.top
        anchors.left: compass.left
        iconSource: "qrc:/icons/yaw_left.svg"
        flat: true
        round: true
        autoRepeat: true
        visible: manual.enabled
        onClicked: manual.addImpact(ManualController.Yaw, -0.05)
    }

    Controls.Button {
        anchors.top: parent.top
        anchors.right: compass.right
        iconSource: "qrc:/icons/yaw_right.svg"
        flat: true
        round: true
        autoRepeat: true
        visible: manual.enabled
        onClicked: manual.addImpact(ManualController.Yaw, 0.05)
    }
}
