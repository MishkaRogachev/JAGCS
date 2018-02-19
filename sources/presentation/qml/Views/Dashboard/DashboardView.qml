import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property var selectedVehicle

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedStep: settings.value("Gui/fdSpeedStep")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property int altitudeStep: settings.value("Gui/fdAltitudeStep")
    property int altitudeUnits: settings.value("Gui/fdAltitudeUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    property string speedSuffix: units.trSpeedUnits(speedUnits)
    property string altitudeSuffix: units.trDistanceUnits(altitudeUnits)

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
        view: dashboard
    }

    implicitWidth: sizings.controlBaseSize * 8 // TODO: display row size

    RowLayout {
        id: row
        width: dashboard.width
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
            tipText: qsTr("Settings")
            flat: true
        }
    }

    Loader {
        id: loader
        anchors.top: row.bottom
        anchors.topMargin: sizings.margins
        width: dashboard.width
        height: Math.min(implicitHeight, dashboard.height - row.height - sizings.spacing)
        clip: true
    }
}
