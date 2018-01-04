import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property var displays

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    implicitWidth: sizings.controlBaseSize * 8 // TODO: display row size

    ListView {
        y: sizings.spacing
        width: parent.width
        height: Math.min(parent.height, contentHeight)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        model: displays

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            Component.onCompleted: {
                switch (display) {
                case DashboardPresenter.ShortVehicleDisplay:
                    setSource("Displays/ShortVehicleDisplay.qml", { "vehicleId": vehicleId });
                    break;
                case DashboardPresenter.FixedWingVehicleDisplay:
                    setSource("Displays/FixedWingVehicleDisplay.qml", { "vehicleId": vehicleId });
                    break;
                default:
                    break;
                }
            }
        }
    }
}
