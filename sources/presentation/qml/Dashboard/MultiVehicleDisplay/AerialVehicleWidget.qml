import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

import "../DashboardControls" as DashboardControls
import "../Vehicles"

Controls.Card {
    id: display

    property int vehicleId: 0

    property AerialVehicle vehicle: AerialVehicle {}

    signal updateCommandStatus(var command, var status)

    function edit() {
        drawer.setMode(DrawerPresenter.Fleet);
        // TODO: deep in concrete vehicle
    }

    onDeepIn: dashboard.selectVehicle(vehicleId)
    onUpdateCommandStatus: {
        switch (command) {
        case Command.SetMode:
            modeBox.status = status;
            break;
        default:
            break;
        }
    }

    menuItems: [
        Controls.MenuItem {
            text: qsTr("Detailed")
            iconSource: "qrc:/icons/flight.svg"
            onTriggered: deepIn()
        },
        Controls.MenuItem {
            text: qsTr("Center")
            iconSource: "qrc:/icons/center.svg"
            highlighted: map.trackingVehicleId === vehicleId
            onTriggered: toggleCentered(vehicleId)
        },
        Controls.MenuItem {
            text: qsTr("Track yaw")
            iconSource: "qrc:/icons/track_yaw.svg"
            highlighted: map.trackingVehicleId === vehicleId && map.trackYaw
            onTriggered: toggleTracked(vehicleId)
        },
        Controls.MenuItem {
            text: qsTr("Edit")
            iconSource: "qrc:/icons/edit.svg"
            onTriggered: edit()
        }
    ]

    implicitWidth: grid.implicitWidth + industrial.margins * 2
    implicitHeight: grid.implicitHeight + industrial.margins * 2

    AerialVehicleDisplayPresenter {
        id: presenter
        view: display
        Component.onCompleted: presenter.setVehicle(vehicleId)
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: industrial.margins
        anchors.rightMargin: parent.margin
        columnSpacing: industrial.spacing
        rowSpacing: industrial.spacing
        columns: 2

        Indicators.YawIndicator {
            id: compass
            implicitWidth: industrial.baseSize * 2.25
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
                fillColor: vehicle.barometric.climb > 0 ? Indicators.Theme.skyColor : Indicators.Theme.groundColor
                minValue: -10
                maxValue: 10 // TODO: to consts
            }
        }

        RowLayout {
            spacing: industrial.spacing

            DashboardControls.Label {
                text: vehicle.vehicleName
                Layout.fillWidth: true
            }

            DashboardControls.ModeBox {
                id: modeBox
                Layout.preferredWidth: industrial.baseSize * 3
                Layout.maximumHeight: industrial.baseSize
            }
        }

        RowLayout {
            spacing: industrial.spacing

            Indicators.ValueLabel {
                digits: 0
                value: units.convertSpeedTo(speedUnits, vehicle.satellite.groundspeed)
                enabled: vehicle.satellite.enabled
                operational: vehicle.satellite.operational
                prefix: qsTr("GS") + ", " + dashboard.speedSuffix
                Layout.fillWidth: true
            }

            Indicators.ValueLabel {
                digits: 0
                value: units.convertSpeedTo(speedUnits, vehicle.pitot.trueAirspeed)
                enabled: vehicle.pitot.enabled
                operational: vehicle.pitot.operational
                prefix: qsTr("TAS") + ", " + dashboard.speedSuffix
                Layout.fillWidth: true
            }

            Indicators.ValueLabel {
                value: units.convertDistanceTo(altitudeUnits, vehicle.barometric.displayedAltitude)
                enabled: vehicle.barometric.enabled
                operational: vehicle.barometric.operational
                prefix: qsTr("Hbar") + ", " + dashboard.altitudeSuffix
                Layout.fillWidth: true
            }
        }
    }
}
