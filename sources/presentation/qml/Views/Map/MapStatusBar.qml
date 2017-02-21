import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtPositioning 5.6

import "qrc:/Controls"
import "qrc:/JS/helper.js" as Helper

Pane {
    id: root

    property var coordinate: QtPositioning.coordinate();

    padding: 0

    RowLayout {
        spacing: 0

        Button {
            id: centerButton
            checkable: true
            iconSource: "qrc:/icons/center.svg"
            enabled: selectedVehicle
            onEnabledChanged: if (!enabled && checked) checked = false
            onCheckedChanged: map.setGesturesEnabled(!checked)

            Connections {
                target: selectedVehicle
                ignoreUnknownSignals: true
                onPositionChanged: {
                    if (!centerButton.checked ||
                        !selectedVehicle.position.coordinate.isValid)
                        return;
                    map.center = selectedVehicle.position.coordinate;
                }
            }
        }

        Button {
            iconSource: "qrc:/icons/layers.svg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: menu.open()

            Menu {
                id: menu
                visible: parent.checked
                width: palette.controlBaseSize * 5

                MenuItem {
                    text: qsTr("Vehicles")
                    checkable: true
                    checked: map.vehicleVisible
                    onCheckedChanged: map.vehicleVisible = checked
                }

                MenuItem {
                    text: qsTr("Track")
                    checkable: true
                    checked: map.trackVisible
                    onCheckedChanged: map.trackVisible = checked
                }

                MenuItem {
                    text: qsTr("Hdop")
                    checkable: true
                    checked: map.hdopVisible
                    onCheckedChanged: map.hdopVisible = checked
                }

                MenuItem {
                    text: qsTr("Mission Points")
                    checkable: true
                    checked: map.missionPointsVisible
                    onCheckedChanged: map.missionPointsVisible = checked
                }

                MenuItem {
                    text: qsTr("Mission Lines")
                    checkable: true
                    checked: map.missionLinesVisible
                    onCheckedChanged: map.missionLinesVisible = checked
                }
            }
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Lat:") + (coordinate.isValid ?
                                      Helper.degreesToDmsString(
                                          coordinate.latitude, false) : "-")
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: palette.fontPixelSize / 1.5
            Layout.fillWidth: true
            text: qsTr("Lon:") + (coordinate.isValid ?
                                      Helper.degreesToDmsString(
                                          coordinate.longitude, true) : "-")
        }
    }
}
