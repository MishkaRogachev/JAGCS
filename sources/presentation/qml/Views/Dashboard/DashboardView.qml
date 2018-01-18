import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property var vehicle
    property var displays

    function selectVehicle(vehicleId) {
        presenter.selectVehicle(vehicleId);
    }

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    implicitWidth: sizings.controlBaseSize * 8 // TODO: display row size

    RowLayout {
        id: unitRow
        width: parent.width
        spacing: sizings.spacing

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            enabled: vehicle !== undefined
            onClicked: selectVehicle(0)
            flat: true
        }

        Controls.Label {
            text: vehicle ? vehicle.name : qsTr("All MAVs")
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/settings.svg"
            tipText: qsTr("Instruments")
            enabled: vehicle !== undefined
            flat: true
        }
    }

    ListView {
        y: unitRow.height + sizings.spacing
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
                case DashboardPresenter.AerialVehicleDisplay:
                    setSource("Displays/AerialVehicleDisplay.qml", { "vehicleId": vehicleId });
                    break;
                default:
                    break;
                }
            }
        }
    }
}
