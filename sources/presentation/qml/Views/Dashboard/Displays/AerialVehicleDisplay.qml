import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../Vehicles"

Item {
    id: vehicleDisplay

    property int vehicleId: 0
    property bool instrumentsUnlocked: false

    property AerialVehicle vehicle: AerialVehicle {}

    signal updateCommandStatus(var command, var status)

    Component.onCompleted: {
         // TODO 5.10 cascading menus
        topbar.serviceMenu.addMenuItem(lockInstruments);
        manual.setVehicleId(vehicleId)
    }

    Component.onDestruction: {
        topbar.serviceMenu.clearMenuItems();
        manual.setVehicleId(0);
    }

    AerialVehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    Controls.MenuItem {
        id: lockInstruments
        text: (checked ? qsTr("Lock") : qsTr("Unlock")) + " " + qsTr("instruments")
        checked: instrumentsUnlocked
        onClicked: instrumentsUnlocked = !instrumentsUnlocked
    }

    ListModel {
        id: instrumentsModel

        ListElement {
            name: qsTr("Diagnostics panel")
            setting: "diagnostics"
            instrument: "../Instruments/DiagnosticsPanel.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Status panel")
            setting: "status"
            instrument: "../Instruments/StatusPanel.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Flight instrument(FD)")
            setting: "fd"
            instrument: "../Instruments/FlightDirector.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Horizontal situation indicator(HSI)")
            setting: "hsi"
            instrument: "../Instruments/HorizontalSituationIndicator.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Landing indicator")
            setting: "landing"
            instrument: "../Instruments/LandingIndicator.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Control panel")
            setting: "control"
            instrument: "../Instruments/ControlPanel.qml"
            instrumentVisible: true
        }
    }

    Repeater {
        model: instrumentsModel

        Controls.MenuItem {
            id: visibilityItem
            text: name
            checkable: true
            onCheckedChanged: instrumentVisible = checked
            onClicked: settings.setValue("veh_" + vehicleId + "/" + setting + "/visibility", checked)
            Component.onCompleted: {
                checked = settings.boolValue("veh_" + vehicleId + "/" + setting + "/visibility", true);
                instrumentVisible = checked;
                topbar.serviceMenu.addMenuItem(visibilityItem)
            }
        }
    }

    Repeater {
        model: instrumentsModel

        Controls.Dragger {
//            x: instrumentX
//            y: instrumentY
            width: sizings.controlBaseSize * 9
            height: loader.height
            visible: instrumentVisible
            dragEnabled: instrumentsUnlocked

            Loader {
                id: loader
                anchors.centerIn: parent
                width: parent.width
                active: instrumentVisible
                source: instrument
            }
        }
    }
}
