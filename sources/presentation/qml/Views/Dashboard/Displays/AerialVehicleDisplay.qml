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
        id: instruments

        ListElement {
            name: qsTr("Diagnostics panel")
            setting: "diagnostics"
            instrument: "../Instruments/DiagnosticsPanel.qml"
        }

        ListElement {
            name: qsTr("Status panel")
            setting: "status"
            instrument: "../Instruments/StatusPanel.qml"
        }

        ListElement {
            name: qsTr("Flight instrument(FD)")
            setting: "fd"
            instrument: "../Instruments/FlightDirector.qml"
        }

        ListElement {
            name: qsTr("Horizontal situation indicator(HSI)")
            setting: "hsi"
            instrument: "../Instruments/HorizontalSituationIndicator.qml"
        }

        ListElement {
            name: qsTr("Landing indicator")
            setting: "landing"
            instrument: "../Instruments/LandingIndicator.qml"
        }

        ListElement {
            name: qsTr("Control panel")
            setting: "control"
            instrument: "../Instruments/ControlPanel.qml"
        }
    }

    Repeater {
        model: instruments

        Controls.MenuItem {
            id: visibilityItem
            text: name
            checkable: true
            checked: settings.boolValue("veh_" + vehicleId + "/" + setting + "/visibility", true)
            onCheckedChanged: {
                if (checked) {
                    for (var i = 0; i < instruments.count; ++i) {
                        var addItem = instruments.get(i);
                        if (addItem.setting !== setting) continue;

                        var order = settings.value("veh_" + vehicleId + "/" +
                                                   addItem.setting + "/order", i);
                        if (order < listModel.count) listModel.insert(order, addItem);
                        else listModel.append(addItem);
                    }
                }
                else {
                    for (var j = 0; j < listModel.count; ++j) {
                        var remItem = listModel.get(j);
                        if (remItem.setting !== setting) continue;

                        listModel.remove(j);
                    }
                }
                settings.setValue("veh_" + vehicleId + "/" + setting + "/visibility", checked);
            }
            Component.onCompleted: topbar.serviceMenu.addMenuItem(visibilityItem)
        }
    }

    ListView {
        id: list
        anchors.top: parent.top
        anchors.right: parent.right
        width: sizings.controlBaseSize * 9
        height: Math.min(contentHeight, vehicleDisplay.height)
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        spacing: sizings.spacing
        model: ListModel { id: listModel }

        delegate: Controls.Dragger {
            width: parent.width
            height: loader.height
            dragEnabled: instrumentsUnlocked
            onDropped: console.log("dropped")

            Loader {
                id: loader
                anchors.centerIn: parent
                width: parent.width
                source: instrument
            }
        }
    }
}
