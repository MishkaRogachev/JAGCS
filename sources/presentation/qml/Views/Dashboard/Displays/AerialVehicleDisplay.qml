import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../Vehicles"

Item {
    id: vehicleDisplay

    property int vehicleId: 0
    property bool instrumentsLocked: false

    property AerialVehicle vehicle: AerialVehicle {}

    signal updateCommandStatus(var command, var status)

    Component.onCompleted: {
        manual.setVehicleId(vehicleId);

        for (var i = 0; i < instruments.count; ++i) {
            var item = instruments.get(i);
            item.visibility = settings.boolValue("veh_" + vehicleId + "/" +
                                                 item.setting + "/visibility");
        }
    }
    Component.onDestruction: manual.setVehicleId(0)

    AerialVehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    ListModel {
        id: instruments

        ListElement {
            name: qsTr("Diagnostics panel")
            setting: "diagnostics"
            instrument: "../Instruments/DiagnosticsPanel.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Status panel")
            setting: "status"
            instrument: "../Instruments/StatusPanel.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Flight instrument(FD)")
            setting: "fd"
            instrument: "../Instruments/FlightDirector.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Horizontal situation indicator(HSI)")
            setting: "hsi"
            instrument: "../Instruments/HorizontalSituationIndicator.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Landing indicator")
            setting: "landing"
            instrument: "../Instruments/LandingIndicator.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Control panel")
            setting: "control"
            instrument: "../Instruments/ControlPanel.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Preparation panel")
            setting: "preparation"
            instrument: "../Instruments/PreparationPanel.qml"
            visibility: false
        }
    }

    ListView {
        id: list
        anchors.top: parent.top
        anchors.right: parent.right
        width: sizings.controlBaseSize * 8
        height: Math.min(contentHeight, vehicleDisplay.height)
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        spacing: sizings.spacing
        footerPositioning: ListView.OverlayFooter
        model: instruments

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            source: instrument
            visible: visibility
            active: visible
            height: visible ? implicitHeight : -list.spacing

            Controls.Button {
                id: itemMenuButton
                anchors.top: parent.top
                anchors.right: parent.right
                enabled: !instrumentsLocked
                iconSource: "qrc:/ui/dots.svg"
                flat: true
                width: sizings.controlBaseSize * 0.5
                height: sizings.controlBaseSize * 0.75
                z: 100
                onClicked: itemMenu.open()

                Controls.Menu {
                    id: itemMenu
                    y: parent.height

                    Controls.MenuItem {
                        width: parent.width
                        iconSource: "qrc:/icons/hide.svg"
                        text: qsTr("Hide")
                        onClicked: visibility = false
                    }
                }
            }
        }

        footer: Item {
            width: parent.width
            height: sizings.controlBaseSize + list.spacing
            z: 10

            Controls.Button {
                enabled: !instrumentsLocked
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width - sizings.controlBaseSize
                iconSource: "qrc:/icons/add.svg"
                text: qsTr("Add")
                onClicked: addMenu.open()

                Controls.Menu {
                    id: addMenu
                    width: parent.width
                    y: parent.height - height

                    Repeater {
                        model: instruments

                        Controls.MenuItem {
                            width: parent.width
                            visible: !visibility
                            height: visible ? implicitHeight : 0
                            text: name
                            onClicked: visibility = true
                        }
                    }
                }
            }

            Controls.Button {
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                checkable: true
                iconSource: checked ? "qrc:/icons/unlock.svg" : "qrc:/icons/lock.svg"
                tipText: (checked ? qsTr("Unlock") : qsTr("Lock")) + " " + qsTr("indicators")
                onCheckedChanged: instrumentsLocked = checked
            }
        }
    }
}
