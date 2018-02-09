import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: root

    property var selectedVehicle

    function selectVehicle(vehicleId) {
        presenter.selectVehicle(vehicleId);
    }

    function updateDisplay() {
        if (selectedVehicle !== undefined) {
            switch (selectedVehicle.type) {
            case Vehicle.FixedWing:
            case Vehicle.FlyingWing:
            default:
                // TODO: Special displays for special types
                loader.setSource("Displays/AerialVehicleDisplay.qml",
                                 { "vehicleId": selectedVehicle.id });
            }
        }
        else {
            loader.setSource("Displays/VehiclesListDisplay.qml")
        }
    }

    Component.onCompleted: updateDisplay()
    onSelectedVehicleChanged: updateDisplay()

    DashboardPresenter {
        id: presenter
        view: root
    }

    implicitWidth: sizings.controlBaseSize * 8 // TODO: display row size

    RowLayout {
        id: row
        width: root.width
        spacing: 0

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            enabled: selectedVehicle !== undefined
            onClicked: selectVehicle(0)
            flat: true
        }

        Controls.Label {
            text: selectedVehicle ? selectedVehicle.name : qsTr("All MAVs")
            font.bold: true
            Layout.fillWidth: true
            clip: true
        }

        Controls.Button {
            id: displaysSettingsButton
            iconSource: "qrc:/icons/settings.svg"
            tipText: qsTr("Instruments")
            enabled: selectedVehicle !== undefined
            flat: true
        }
    }

    Loader {
        id: loader
        anchors.top: row.bottom
        anchors.topMargin: sizings.spacing
        width: root.width
        height: Math.min(implicitHeight, root.height - sizings.spacing)
        clip: true
    }
}
