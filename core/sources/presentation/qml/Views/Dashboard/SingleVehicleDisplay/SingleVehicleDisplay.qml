import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../Vehicles"
import "../"

BaseDisplay {
    id: display

    property int vehicleId: 0
    property bool instrumentsUnlocked: false

    property AerialVehicle vehicle: AerialVehicle {}

    signal updateCommandStatus(var command, var status)

    Component.onCompleted: {
        topbarOffset = topBarDelegate.width;
        manual.setVehicleId(vehicleId);

        for (var i = 0; i < instruments.count; ++i) {
            var item = instruments.get(i);
            item.visibility = settings.boolValue("veh_" + vehicleId + "/" +
                                                 item.setting + "/visibility");
            if (item.visibility) instruments.visibleItems++;
        }

        map.xCenterOffset = Qt.binding(function() {
            return cornerMap || !dashboardVisible ? 0 : list.width / 2;
        });
    }
    Component.onDestruction: manual.setVehicleId(0)

    implicitWidth: list.width + sizings.margins
    implicitHeight: list.contentHeight + topBarDelegate.height

    AerialVehicleDisplayPresenter {
        id: presenter
        view: display
        Component.onCompleted: setVehicle(vehicleId)
    }

    TopBarDelegate {
        id: topBarDelegate
        anchors.right: parent.right
        width: parent.width
    }

    ListModel {
        id: instruments

        property int visibleItems: 0

        ListElement {
            name: qsTr("Diagnostics panel")
            setting: "diagnostics"
            instrument: "Instruments/DiagnosticsPanel.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Status panel")
            setting: "status"
            instrument: "Instruments/StatusPanel.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Flight instrument(FD)")
            setting: "fd"
            instrument: "Instruments/FlightDirector.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Horizontal situation indicator(HSI)")
            setting: "hsi"
            instrument: "Instruments/HorizontalSituationIndicator.qml"
            visibility: false
        }

        ListElement {
            name: qsTr("Landing indicator")
            setting: "landing"
            instrument: "Instruments/LandingIndicator.qml"
            visibility: false
        }
    }

    ListView {
        id: list
        anchors.top: topBarDelegate.bottom
        anchors.topMargin: sizings.spacing
        anchors.right: parent.right
        anchors.rightMargin: sizings.margins
        width: dashboardWidth
        height: Math.min(parent.height - topBarDelegate.height - sizings.spacing, contentHeight)
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        spacing: sizings.spacing
        footerPositioning: ListView.OverlayFooter
        visible: dashboardVisible
        model: instruments
        clip: true

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
                enabled: instrumentsUnlocked
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
                        onClicked: {
                            visibility = false;
                            settings.setValue("veh_" + vehicleId + "/" +
                                              setting + "/visibility", false);
                            instruments.visibleItems--;
                        }
                    }
                }
            }
        }

        footer: Item {
            width: parent.width
            visible: instrumentsUnlocked && instruments.visibleItems < instruments.count
            height: visible ? sizings.controlBaseSize + list.spacing : 0
            z: 10

            Controls.Button {
                width: parent.width
                anchors.bottom: parent.bottom
                iconSource: "qrc:/ui/plus.svg"
                text: qsTr("Add")
                onClicked: addMenu.open()

                Controls.Menu {
                    id: addMenu
                    width: parent.width

                    Repeater {
                        model: instruments

                        Controls.MenuItem {
                            width: parent.width
                            visible: !visibility
                            height: visible ? implicitHeight : 0
                            text: name
                            onClicked: {
                                visibility = true;
                                settings.setValue("veh_" + vehicleId + "/" +
                                                  setting + "/visibility", true);
                                instruments.visibleItems++;
                            }
                        }
                    }
                }
            }
        }
    }
}
