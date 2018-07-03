import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

BaseDisplay {
    id: listDisplay

    property var vehicles
    property bool showOffline: true

    onShowOfflineChanged: vehicles.showOffline = showOffline
    Component.onCompleted: {
        topbarOffset = topBarDelegate.width;
        map.xCenterOffset = Qt.binding(function() {
            return cornerMap || !dashboardVisible ? 0 : list.width / 2;
        });
    }

    implicitWidth: Math.max(list.width + sizings.margins, topBarDelegate.width)
    implicitHeight: list.contentHeight + topBarDelegate.height

    VehiclesListDisplayPresenter {
        id: presenter
        view: listDisplay
    }

    TopBarDelegate {
        id: topBarDelegate
        anchors.right: parent.right
    }

    ListView {
        id: list
        anchors.top: topBarDelegate.bottom
        anchors.topMargin: sizings.spacing
        anchors.right: parent.right
        anchors.rightMargin: sizings.margins
        width: dashboardWidth
        height: Math.min(parent.height - topBarDelegate.height - sizings.spacing, contentHeight)
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        visible: dashboardVisible
        model: vehicles
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: Loader {
            property int displayVehicleId: vehicleId

            width: parent.width - sizings.shadowSize
            onDisplayVehicleIdChanged: {
                setSource("");
                switch (vehicleType) {
                case Vehicle.FixedWing:
                case Vehicle.FlyingWing:
                default:
                    // TODO: Special widgets for different vehicles
                    return setSource("AerialVehicleWidget.qml", { "vehicleId": displayVehicleId });
                }
            }
        }
    }
}
