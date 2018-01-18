import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: root

    property var selectedVehicle
    property var displays

    function selectVehicle(vehicleId) {
        presenter.selectVehicle(vehicleId);
    }

    DashboardPresenter {
        id: presenter
        view: root
    }

    implicitWidth: sizings.controlBaseSize * 8 // TODO: display row size

    RowLayout {
        id: unitRow
        spacing: sizings.spacing

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            enabled: selectedVehicle !== undefined
            onClicked: selectVehicle(0)
            flat: true
        }

        Controls.Label {
            text: selectedVehicle ? selectedVehicle.name : qsTr("All MAVs")
            font.bold: true
        }

        Controls.Button {
            id: displaysSettingsButton
            iconSource: "qrc:/icons/settings.svg"
            tipText: qsTr("Instruments")
            enabled: selectedVehicle !== undefined
            flat: true
        }
    }

    ListView {
        y: unitRow.height + sizings.spacing
        width: root.width
        height: Math.min(parent.height, contentHeight + sizings.shadowSize)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        model: displays

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width - sizings.shadowSize
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
