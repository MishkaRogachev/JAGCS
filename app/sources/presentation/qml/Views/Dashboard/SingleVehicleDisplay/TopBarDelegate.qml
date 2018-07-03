import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../DashboardControls" as DashboardControls

Controls.Pane {
    id: topbarDelegate

    readonly property int waypointCount: vehicle.mission.count
    readonly property int waypointCurrent: vehicle.mission.current

    padding: 0

    Component.onCompleted: updateItems()
    onWaypointCurrentChanged: updatewaypointCurrent()
    onWaypointCountChanged: updateItems()

    function updateItems() {
        var items = [];
        for (var i = 0; i < waypointCount; ++i) items.push(i + 1);
        waypointBox.model = items;
    }

    function updatewaypointCurrent() {
        waypointBox.currentIndex = waypointCurrent;
    }

    Connections {
        target: display
        onUpdateCommandStatus: {
            switch (command) {
            case Command.SetMode:
                modeBox.status = status;
                break;
            case Command.GoTo:
                waypointBox.status = status;
                break;
            default:
                break;
            }
        }
    }

    Connections {
        target: map
        onGoTo: waypointBox.goTo(index)
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            spacing: 0

            Controls.Button {
                iconSource: "qrc:/icons/left.svg"
                tipText: qsTr("Overview")
                flat: true
                onClicked: dashboard.selectVehicle(0)
            }

            DashboardControls.Label {
                text: selectedVehicle !== undefined ? selectedVehicle.name : qsTr("No vehicle")
                Layout.fillWidth: true
            }

            DashboardControls.ModeBox {
                id: modeBox
                Layout.preferredWidth: sizings.controlBaseSize * 4
                Layout.maximumHeight: sizings.controlBaseSize
            }

            Controls.Button {
                iconSource: dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                               "qrc:/icons/show_dashboard.svg"
                tipText: (dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                         " " + qsTr("dashboard")
                flat: true
                onClicked: dashboardVisible = !dashboardVisible
                Layout.fillHeight: true
            }
        }

        RowLayout {
            spacing: 0

            Controls.Button {
                id: preparationButton
                iconSource: "qrc:/icons/calibrate.svg"
                tipText: (preparationPanel.visible ? qsTr("Close") : qsTr("Open")) + " " +
                         qsTr("preparation panel")
                flat: true
                onClicked: preparationPanel.visible ? preparationPanel.close() :
                                                      preparationPanel.open()

                PreparationPanel {
                    id: preparationPanel
                    x: -width - sizings.spacing
                }
            }

            Controls.Button {
                id: centerButton
                iconSource: "qrc:/icons/center.svg"
                iconColor: map.trackingVehicleId === vehicleId ? customPalette.highlightColor :
                                                                 customPalette.textColor
                tipText: qsTr("Track vehicle")
                flat: true
                enabled: map.visible
                onEnabledChanged: if (!enabled) trackMenu.close()
                onClicked: trackMenu.visible ? trackMenu.close() : trackMenu.open()

                Controls.Menu {
                    id: trackMenu
                    y: centerButton.height

                    Controls.MenuItem {
                        iconSource: "qrc:/icons/center.svg"
                        text: qsTr("Center vehicle")
                        highlighted: map.trackingVehicleId == vehicleId
                        onTriggered: toggleCentered(vehicleId)
                    }

                    Controls.MenuItem {
                        iconSource: "qrc:/icons/track_yaw.svg"
                        text: qsTr("Track yaw")
                        highlighted: map.trackingVehicleId == vehicleId && map.trackYaw
                        onTriggered: toggleTracked(vehicleId)
                    }
                }
            }

            Controls.Button {
                iconSource: "qrc:/icons/joystick.svg"
                tipText: (manual.enabled ? qsTr("Disable") : qsTr("Enable")) +
                         " " + qsTr("manual control")
                iconColor: manual.enabled ? customPalette.highlightColor : customPalette.textColor
                flat: true
                onClicked: manual.setEnabled(!manual.enabled)
            }

            Item {
                Layout.fillWidth: true
            }

            DashboardControls.WaypointBox {
                id: waypointBox
                Layout.preferredWidth: sizings.controlBaseSize * 4
                Layout.maximumHeight: sizings.controlBaseSize
            }

            Controls.Button {
                id: lockButton
                enabled: dashboardVisible
                iconSource: instrumentsUnlocked ? "qrc:/icons/lock.svg" : "qrc:/icons/unlock.svg"
                tipText: (instrumentsUnlocked ? qsTr("Lock") : qsTr("Unlock")) + " " +
                         qsTr("indicators")
                flat: true
                onClicked: instrumentsUnlocked = !instrumentsUnlocked
            }
        }
    }
}
