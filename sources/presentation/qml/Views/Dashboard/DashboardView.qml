import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property int vehicleId: 0
    property var instruments: []

    function setActiveVehicle(vehicleId) {
        dashboard.vehicleId = vehicleId;
        presenter.setVehicle(vehicleId);
    }

    implicitWidth: sizings.controlBaseSize * 9

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    ListView {
        y: sizings.spacing
        width: parent.width
        height: Math.min(parent.height, contentHeight)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        model: instruments

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            source: createIndicator(modelData)
        }
    }

    function createIndicator(instrument) {
        switch (instrument) {
        case DashboardPresenter.SatelliteDispaly: return "Instruments/SatelliteDisplay.qml";
        case DashboardPresenter.FlightDisplay: return "Instruments/FlightDisplay.qml";
        case DashboardPresenter.NavigationDisplay: return "Instruments/NavigationDisplay.qml";
        //case "battery": return Qt.createComponent("Instruments/BatteryDisplay.qml");
        //case "status": return Qt.createComponent("Instruments/StatusDisplay.qml");
        //case "mission": return Qt.createComponent("Instruments/MissionDisplay.qml");
        default: return null
        }
    }
}
