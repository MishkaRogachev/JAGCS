import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: listDisplay

    property var vehicles

    VehiclesListDisplayPresenter {
        id: presenter
        view: listDisplay
    }

    ListView {
        id: list
        anchors.top: parent.top
        anchors.right: parent.right
        width: sizings.controlBaseSize * 9
        height: Math.min(parent.height, contentHeight)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
        headerPositioning: ListView.OverlayHeader
        model: vehicles

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        header: Item {
            width: parent.width
            height: pane.height + list.spacing
            z: 10

            Controls.Pane {
                id: pane
                width: parent.width
                height: sizings.controlBaseSize + padding * 2

                Controls.CheckBox {
                    anchors.centerIn: parent
                    width: parent.width - padding * 2
                    text: qsTr("Show offline")
                    checked: vehicles.showOffline
                    onClicked: vehicles.setShowOffline(!vehicles.showOffline)
                }
            }
        }

        delegate: Loader {
            property int displayType: vehicleType
            property int displayVehicleId: vehicleId

            width: parent.width - sizings.shadowSize

            onDisplayVehicleIdChanged: setupDisplay()
            Component.onCompleted: setupDisplay()

            function setupDisplay() {
                switch (displayType) {
                case Vehicle.FixedWing:
                case Vehicle.FlyingWing:
                default:
                    // TODO: Special widgets for different vehicles
                    return setSource("AerialVehicleWidget.qml",
                                     { "vehicleId": displayVehicleId });
                }
            }
        }
    }
}
