import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: listDisplay

    property var vehicles
    property bool showOffline: true

    property alias dashboardVisible: list.visible

    onShowOfflineChanged: vehicles.showOffline = showOffline

    implicitWidth: list.width + sizings.margins

    VehiclesListDisplayPresenter {
        id: presenter
        view: listDisplay
    }

    TopBarDelegate {
        id: topBarDelegate
        width: parent.width
    }

    ListView {
        id: list
        anchors.top: topBarDelegate.bottom
        anchors.topMargin: sizings.spacing
        anchors.right: parent.right
        anchors.rightMargin: sizings.margins
        width: sizings.controlBaseSize * 9
        height: Math.min(parent.height - topBarDelegate.height - sizings.spacing, contentHeight)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        snapMode: ListView.SnapToItem
        headerPositioning: ListView.OverlayHeader
        model: vehicles
        clip: true

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
                    // TODO: Special widgets for different vehicles
                    return setSource("AerialVehicleWidget.qml",
                                     { "vehicleId": displayVehicleId });
                }
            }
        }
    }
}
