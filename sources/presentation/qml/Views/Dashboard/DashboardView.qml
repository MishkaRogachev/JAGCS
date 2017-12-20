import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property int selectedVehicle: 0
    property var instruments: []

    function selectVehicle(vehicleId) {
        selectedVehicle = vehicleId;
        presenter.setVehicle(vehicleId);
    }

    implicitWidth: sizings.controlBaseSize * 8 // TODO: instruments row size

    DashboardPresenter {
        id: presenter
        view: dashboard
        Component.onCompleted: updateSelection()
    }

    ListView {
        y: sizings.spacing
        width: parent.width
        height: Math.min(parent.height, contentHeight)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        model: instruments

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            Component.onCompleted: {
                switch (instrument) {
                case DashboardPresenter.VehicleDispaly:
                    setSource("Displays/VehicleDisplay.qml",
                              { "vehicleId": vehicleId });
                    break;
                case DashboardPresenter.SatelliteDispaly:
                    setSource("Displays/SatelliteDisplay.qml",
                              { "vehicleId": vehicleId });
                    break;
                case DashboardPresenter.FlightDisplay:
                    setSource("Displays/FlightDisplay.qml",
                              { "vehicleId": vehicleId });
                    break;
                case DashboardPresenter.NavigationDisplay:
                    setSource("Displays/NavigationDisplay.qml",
                              { "vehicleId": vehicleId });
                    break;
                case DashboardPresenter.ControlDisplay:
                    setSource("Displays/ControlDisplay.qml",
                              { "vehicleId": vehicleId });
                    break;
                case DashboardPresenter.MissionDisplay:
                    setSource("Displays/MissionDisplay.qml",
                              { "vehicleId": vehicleId });
                    break;
                default:
                    break;
                }
            }
        }
    }
}
