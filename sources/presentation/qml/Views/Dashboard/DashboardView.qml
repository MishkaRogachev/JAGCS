import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
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

    spacing: sizings.spacing

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    RowLayout {
        id: row
        spacing: 0

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            tipText: qsTr("Overview")
            enabled: selectedVehicle !== undefined
            onClicked: selectVehicle(0)
            flat: true
        }

        Controls.Button {
            visible: selectedVehicle !== undefined
            iconSource: "qrc:/icons/joystick.svg"
            tipText: (manual.enabled ? qsTr("Disable") : qsTr("Enable")) +
                     " " + qsTr("manual control")
            iconColor: manual.enabled ? customPalette.selectionColor : customPalette.textColor
            onClicked: manual.setEnabled(!manual.enabled)
            flat: true
        }

        Controls.Button {
            id: displaysSettingsButton
            iconSource: "qrc:/icons/service.svg"
            tipText: qsTr("Service")
            flat: true
        }

        Controls.Label {
            text: selectedVehicle !== undefined ? selectedVehicle.name : qsTr("All MAVs")
            font.bold: true
            Layout.fillWidth: true
            clip: true
        }
    }

    Loader {
        id: loader
        clip: true
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
