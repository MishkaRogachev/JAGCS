import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property var instruments: []

    function setActiveVehicle(vehicleId) {
        presenter.setVehicle(vehicleId);
    }

    implicitWidth: sizings.controlBaseSize * 11

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    ListView {
        anchors.fill: parent
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        model: linkIds

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: Loader {
            width: parent.width
        }
    }
}

/*Repeater {
    id: root

    property var instruments

    property url vehicleMark
    property bool online: false

    signal instrumentAdded(string name, QtObject view)

    model: instruments

    Loader {
        sourceComponent: createIndicator(modelData)
        onItemChanged: if (item) instrumentAdded(modelData, item)
        Layout.alignment: Qt.AlignTop
        Layout.minimumHeight: item ? item.minimumHeight : 0
        Layout.maximumHeight: item ? item.maximumHeight : 0
        Layout.preferredHeight: (Layout.minimumHeight + Layout.maximumHeight) / 2
        Layout.fillWidth: true
        Layout.fillHeight: true

        function createIndicator(modelData) {
            switch (modelData) {
            case "satellite": return Qt.createComponent("Displays/SatelliteDisplay.qml");
            case "fd": return Qt.createComponent("Displays/FlightDisplay.qml");
            case "navigator": return Qt.createComponent("Displays/NavigationDisplay.qml");
            case "battery": return Qt.createComponent("Displays/BatteryDisplay.qml");
            case "status": return Qt.createComponent("Displays/StatusDisplay.qml");
            case "mission": return Qt.createComponent("Displays/MissionDisplay.qml");
            default: return null
            }
        }
    }
}*/
