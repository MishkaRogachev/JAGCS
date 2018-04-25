import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../Vehicles"

Item {
    id: vehicleDisplay

    property int vehicleId: 0

    property AerialVehicle vehicle: AerialVehicle {}

    signal updateCommandStatus(var command, var status)

    Component.onCompleted: manual.setVehicleId(vehicleId)
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
        model: ListModel { id: listModel }

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            width: parent.width
            source: instrument
        }

        footer: Item {
            width: parent.width
            height: sizings.controlBaseSize + list.spacing
            z: 10

            Controls.Button {
                enabled: !lockButton.checked
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                width: parent.width - sizings.controlBaseSize
                iconSource: "qrc:/icons/service.svg"
                text: qsTr("Instruments")
                onClicked: instrumentsMenu.open()

                Controls.Popup {
                    id: instrumentsMenu
                    width: parent.width
                    y: parent.height - height

                    ColumnLayout {
                        anchors.fill: parent

                        Repeater {
                            model: instruments

                            Controls.CheckBox {
                                text: name
                                Layout.fillWidth: true
                                checked: settings.boolValue("veh_" + vehicleId + "/" +
                                                            setting + "/visibility", true)
                                onCheckedChanged: {
                                    if (checked) {
                                        for (var i = 0; i < instruments.count; ++i) {
                                            var addItem = instruments.get(i);
                                            if (addItem.setting !== setting) continue;

                                            var order = settings.value("veh_" + vehicleId + "/" +
                                                                       addItem.setting + "/order", i);
                                            if (order < listModel.count)
                                            {
                                                listModel.insert(order, addItem);
                                            }
                                            else listModel.append(addItem);
                                            settings.setValue("veh_" + vehicleId + "/" +
                                                              setting + "/order", order);
                                        }
                                    }
                                    else {
                                        for (var j = 0; j < listModel.count; ++j) {
                                            var remItem = listModel.get(j);
                                            if (remItem.setting !== setting) continue;

                                            listModel.remove(j);
                                        }
                                    }
                                    settings.setValue("veh_" + vehicleId + "/" +
                                                      setting + "/visibility", checked);
                                }
                            }
                        }
                    }
                }
            }

            Controls.Button {
                id: lockButton
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                checkable: true
                iconSource: checked ? "qrc:/icons/unlock.svg" : "qrc:/icons/lock.svg"
                tipText: (checked ? qsTr("Unlock") : qsTr("Lock")) + " " + qsTr("indicators")
            }
        }
    }
}
