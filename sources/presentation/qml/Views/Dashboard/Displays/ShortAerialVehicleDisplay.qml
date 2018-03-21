import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

import "../DashboardControls" as DashboardControls
import "../Vehicles"

Controls.Card {
    id: vehicleDisplay

    property int vehicleId: 0

    property AerialVehicle vehicle: AerialVehicle {}

    AerialVehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    onVehicleIdChanged: presenter.setVehicle(vehicleId)
    onDeepIn: dashboard.selectVehicle(vehicleId)

    implicitWidth: grid.implicitWidth + sizings.margins * 2
    implicitHeight: grid.implicitHeight + sizings.margins * 2

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: sizings.margins
        columnSpacing: sizings.spacing
        rowSpacing: sizings.spacing
        columns: 2

        Indicators.YawIndicator {
            id: compass
            implicitWidth: sizings.controlBaseSize * 2
            implicitHeight: width
            yaw: vehicle.ahrs.yaw
            Layout.rowSpan: 2

            Indicators.BarIndicator {
                anchors.verticalCenter: ah.verticalCenter
                anchors.right: ah.left
                width: ah.width * 0.1
                height: ah.height * 0.6
                value: vehicle.powerSystem.throttle
            }

            Indicators.ArtificialHorizon {
                id: ah
                anchors.centerIn: parent
                height: parent.height - parent.size * 2
                width: height * 0.7
                enabled: vehicle.online && vehicle.ahrs.enabled
                armed: vehicle.armed
                pitch: vehicle.ahrs.pitch
                roll: vehicle.ahrs.roll
                rollInverted: dashboard.rollInverted
            }

            Indicators.BarIndicator {
                anchors.verticalCenter: ah.verticalCenter
                anchors.left: ah.right
                width: ah.width * 0.1
                height: ah.height * 0.6
                value: vehicle.barometric.climb
                fillColor: vehicle.barometric.climb > 0 ? palette.skyColor :
                                                          palette.groundColor
                minValue: -10
                maxValue: 10 // TODO: to consts
            }
        }

        RowLayout {
            spacing: sizings.spacing

            Controls.Label {
                text: vehicle.vehicleName
                font.bold: true
                Layout.maximumWidth: sizings.controlBaseSize * 3
            }

            DashboardControls.Label {
                text: translator.translateVehicleMode(vehicle.mode)
                horizontalAlignment: Text.AlignRight
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: sizings.spacing

            Indicators.ValueLabel2 {
                digits: 0
                value: units.convertSpeedTo(speedUnits, vehicle.satellite.groundspeed)
                enabled: vehicle.satellite.enabled
                operational: vehicle.satellite.operational
                prefix: qsTr("GS") + ", " + dashboard.speedSuffix
                Layout.fillWidth: true
            }

            Indicators.ValueLabel2 {
                digits: 0
                value: units.convertSpeedTo(speedUnits, vehicle.pitot.trueAirspeed)
                enabled: vehicle.pitot.enabled
                operational: vehicle.pitot.operational
                prefix: qsTr("TAS") + ", " + dashboard.speedSuffix
                Layout.fillWidth: true
            }

            Indicators.ValueLabel2 {
                value: units.convertDistanceTo(altitudeUnits, vehicle.barometric.displayedAltitude)
                enabled: vehicle.barometric.enabled
                operational: vehicle.barometric.operational
                prefix: qsTr("ALT") + ", " + dashboard.altitudeSuffix
                Layout.fillWidth: true
            }
        }
    }
}
