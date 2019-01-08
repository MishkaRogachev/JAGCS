import QtQuick 2.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: dashboard

    property var selectedVehicle

    property int topbarOffset: 0
    property bool dashboardVisible: true
    property int dashboardWidth: industrial.baseSize * 8

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedStep: settings.value("Gui/fdSpeedStep")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property int altitudeStep: settings.value("Gui/fdAltitudeStep")
    property int altitudeUnits: settings.value("Gui/fdAltitudeUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    property string speedSuffix: units.trSpeedUnits(speedUnits)
    property string altitudeSuffix: units.trDistanceUnits(altitudeUnits)

    function selectVehicle(vehicleId) { // TODO: to vehicle controller
        presenter.selectVehicle(vehicleId);
    }

    function updateDisplay() {
        if (selectedVehicle !== undefined) {
            loader.setSource("SingleVehicleDisplay/SingleVehicleDisplay.qml",
                             { "vehicleId": selectedVehicle.id });
        } else {
            loader.setSource("MultiVehicleDisplay/MultiVehicleDisplay.qml");
        }
    }

    Component.onCompleted: updateDisplay()
    onSelectedVehicleChanged: updateDisplay()

    width: loader.implicitWidth
    implicitHeight: loader.implicitHeight

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    Loader {
        id: loader
        height: parent.height
        clip: true
    }
}
