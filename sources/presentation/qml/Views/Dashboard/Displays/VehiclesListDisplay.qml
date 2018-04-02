import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: listDisplay

    property var vehicles

    implicitHeight: list.contentHeight + sizings.shadowSize

    Component.onCompleted: serviceMenu.addMenuItem(showOffline)
    Component.onDestruction: serviceMenu.clearMenuItems()

    VehiclesListDisplayPresenter {
        id: presenter
        view: listDisplay
    }

    Controls.MenuItem {
        id: showOffline
        text: qsTr("Show offline")
        checked: vehicles.showOffline
        onClicked: vehicles.setShowOffline(!vehicles.showOffline)
    }

    ListView {
        id: list
        width: listDisplay.width - sizings.shadowSize
        height: parent.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        model: vehicles

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
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
                    // TODO: Special short displays for special types
                    return setSource("ShortAerialVehicleDisplay.qml",
                                     { "vehicleId": displayVehicleId });
                }
            }
        }
    }
}
