import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../Vehicles"

Item {
    id: vehicleDisplay

    property int vehicleId: 0
    property bool instrumentsUnlocked: true

    property AerialVehicle vehicle: AerialVehicle {}

    signal updateCommandStatus(var command, var status)

    implicitWidth: list.contentWidth
    implicitHeight: list.contentHeight + sizings.shadowSize

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
        checked: !instrumentsUnlocked
        onClicked: instrumentsUnlocked = !instrumentsUnlocked
    }

    ListModel {
        id: instrumentsModel

        ListElement {
            name: qsTr("Diagnostics panel")
            setting: "diagnosticsVisible"
            instrument: "../Instruments/DiagnosticsPanel.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Status panel")
            setting: "statusVisible"
            instrument: "../Instruments/StatusPanel.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Flight instrument(FD)")
            setting: "fdVisible"
            instrument: "../Instruments/FlightDirector.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Horizontal situation indicator(HSI)")
            setting: "hsiVisible"
            instrument: "../Instruments/HorizontalSituationIndicator.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Landing indicator")
            setting: "landingVisible"
            instrument: "../Instruments/LandingIndicator.qml"
            instrumentVisible: true
        }

        ListElement {
            name: qsTr("Control panel")
            setting: "controlVisible"
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
            onClicked: settings.setValue("veh_" + vehicleId + "/" + setting, checked)
            Component.onCompleted: {
                checked = settings.boolValue("veh_" + vehicleId + "/" + setting, true);
                instrumentVisible = checked;
                topbar.serviceMenu.addMenuItem(visibilityItem)
            }
        }
    }

    ListView {
        id: list
        anchors.top: parent.top
        anchors.right: parent.right
        width: sizings.controlBaseSize * 9
        height: Math.min(parent.height, contentHeight)
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        spacing: sizings.spacing
        model: instrumentsModel

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            active: instrumentVisible
            height: active && item ? item.implicitHeight : -list.spacing
            source: instrument
        }
    }
}
