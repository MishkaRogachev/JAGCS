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

    onUpdateCommandStatus: {
        switch (command) {
        case Command.SetMode:
            modeBox.status = status;
            break;
        default:
            break;
        }
    }

    Component.onCompleted: {
        menu.addEntry(qsTr("Detailed"), "qrc:/icons/flight.svg").triggered.connect(deepIn);

        var center = menu.addEntry(qsTr("Center vehicle"), "qrc:/icons/center.svg");
        center.highlighted = Qt.binding(function() { return map.trackingVehicleId == vehicleId; });
        center.triggered.connect(function() { toggleCentered(vehicleId) });

        var track = menu.addEntry(qsTr("Track yaw"), "qrc:/icons/track_yaw.svg");
        track.highlighted = Qt.binding(function() { return map.trackingVehicleId == vehicleId &&
                                                           map.trackYaw; });
        track.triggered.connect(function() { toggleTracked(vehicleId) });

        menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);
    }

    onDeepIn: dashboard.selectVehicle(vehicleId)

    AerialVehicleDisplayPresenter {
        id: presenter
        view: display
        Component.onCompleted: presenter.setVehicle(vehicleId)
    }

    implicitWidth: grid.implicitWidth + controlSize.margins * 2
    implicitHeight: grid.implicitHeight + controlSize.margins * 2

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: controlSize.margins
        anchors.rightMargin: parent.margin
        columnSpacing: controlSize.spacing
        rowSpacing: controlSize.spacing
        columns: 2

        Indicators.YawIndicator {
            id: compass
            implicitWidth: controlSize.baseSize * 2.25
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
                fillColor: vehicle.barometric.climb > 0 ? customPalette.skyColor :
                                                          customPalette.groundColor
                minValue: -10
                maxValue: 10 // TODO: to consts
            }
        }

        RowLayout {
            spacing: controlSize.spacing

            DashboardControls.Label {
                text: vehicle.vehicleName
                Layout.fillWidth: true
            }

            DashboardControls.ModeBox {
                id: modeBox
                Layout.preferredWidth: controlSize.baseSize * 3
                Layout.maximumHeight: controlSize.baseSize
            }
        }

        RowLayout {
            spacing: controlSize.spacing

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
