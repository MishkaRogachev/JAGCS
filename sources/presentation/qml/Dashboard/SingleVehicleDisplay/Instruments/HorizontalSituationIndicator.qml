import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

BaseInstrument {
    id: root

    implicitHeight: width * 0.6

    Indicators.DistanceLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("DIST") + ", " + distancePrefix
        active: vehicle.guided
        distance: vehicle.navigator.targetDistance
        width: parent.width * 0.2
    }

    Indicators.DistanceLabel {
        id: homeLabel
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        prefix: qsTr("HOME") + ", " + distancePrefix
        distance: vehicle.position.distanceTo(vehicle.home.position)
        width: parent.width * 0.2
    }

    Indicators.ValueLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: parent.width * 0.2
        prefix: qsTr("WIND") + ", " + dashboard.speedSuffix
        value: units.convertSpeedTo(dashboard.speedUnits, vehicle.wind.speed)
        enabled: value > 0
    }

    Indicators.Compass {
        id: compass
        anchors.centerIn: parent
        height: parent.height - industrial.padding
        width: height
        mark: translator.imageFromVehicleType(vehicle.vehicleType)
        heading: vehicle.compass.heading
        enabled: vehicle.compass.enabled
        operational: vehicle.compass.operational
        course: vehicle.satellite.course
        courseEnabled: vehicle.satellite.groundspeed > 0.1
        courseColor: vehicle.satellite.enabled ? (vehicle.satellite.operational ?
                              Indicators.Theme.positiveColor : Indicators.Theme.dangerColor) :
                                                 "transparent"

        Indicators.SituationIndicator {
            id: hsi
            anchors.fill: parent
            guided: vehicle.guided
            heading: compass.safeHeading
            targetBearing: vehicle.navigator.targetBearing
            desiredHeading: vehicle.flightControl.desiredHeading
            trackError: vehicle.navigator.trackError
            z: -1
        }

        Item {
            anchors.fill: parent
            rotation: vehicle.position.azimuthTo(vehicle.home.position) - vehicle.compass.heading
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

    Indicators.ValueLabel {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: itemMenuButton.width / 2
        active: vehicle.guided
        value: vehicle.navigator.targetBearing
        width: parent.width * 0.2
        prefix: qsTr("TRG") + ", \u00B0"
    }

    Indicators.ValueLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        value: vehicle.compass.heading
        width: parent.width * 0.2
        visible: vehicle.compass.present
        enabled: vehicle.compass.enabled
        operational: vehicle.compass.operational
        prefix: qsTr("HDG") + ", \u00B0"
    }

    Indicators.ValueLabel {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        value: vehicle.satellite.course
        width: parent.width * 0.2
        visible: vehicle.satellite.present
        enabled: vehicle.satellite.enabled
        operational: vehicle.satellite.operational
        prefix: qsTr("CRS") + ", \u00B0"
    }

    Controls.Button {
        anchors.top: parent.top
        anchors.left: compass.left
        iconSource: "qrc:/icons/yaw_left.svg"
        flat: true
        round: true
        autoRepeat: true
        enabled: vehicle.online && vehicle.ahrs.enabled
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
        enabled: vehicle.online && vehicle.ahrs.enabled
        visible: manual.enabled
        onClicked: manual.addImpact(ManualController.Yaw, 0.05)
    }
}
