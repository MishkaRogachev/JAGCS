import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

import "../Video"

Pane {
    id: root

    property QtObject commandHelper
    property var vehicleNames
    property alias selectedVehicle: vehicleView.vehicle

    property bool cornerMap: false
    property bool cornerVisible: true

    signal vehicleSelected(string name)

    padding: 0

    Item {
        id: background
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: sidebar.right
        anchors.right: parent.right
    }

    Item {
        id: corner
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: parent.width / 4
        height: cornerVisible ? width * 3 / 4 : 0// TODO: ratio
    }

    FlightMapView {
        id: map
        objectName: "map"
        anchors.fill: cornerMap ? corner : background
        z: cornerMap
    }

    VideoView {
        objectName: "video"
        anchors.fill: cornerMap ? background : corner
    }

    RowLayout {
        anchors.bottom: corner.top
        anchors.left: corner.left
        z: 2

        Button {
            onClicked: cornerVisible = !cornerVisible
            iconSource: cornerVisible ? "qrc:/ui/hide.svg" : "qrc:/ui/show.svg"
        }

        Button {
            onClicked: cornerMap = !cornerMap
            iconSource: cornerMap ? "qrc:/icons/map-marker.svg" : "qrc:/icons/video.svg"
        }
    }


    Item {
        id: sidebar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: column.width

        ColumnLayout {
            id: column
            height: parent.height

            RowLayout {

                ComboBox {
                    model: vehicleNames
                    Layout.fillWidth: true
                    onCurrentTextChanged: vehicleSelected(currentText)
                }

                Button {
                    id: centerButton
                    checkable: true
                    iconSource: "qrc:/icons/center.svg"
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
            }

            VehicleView {
                id: vehicleView
                Layout.fillWidth: true
            }

            Item {
                width: 1
                Layout.fillHeight: true
            }
        }
    }
}
