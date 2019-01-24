import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "../"

BaseDisplay {
    id: listDisplay

    property var vehicles
    property bool showOffline: true

    signal updateCommandStatus(var command, var status)

    onShowOfflineChanged: vehicles.showOffline = showOffline
    Component.onCompleted: {
        topbarOffset = topBarDelegate.width;
        map.xCenterOffset = Qt.binding(function() {
            return cornerMap || !dashboardVisible ? 0 : list.width / 2;
        });
    }

    implicitWidth: Math.max(list.width + controlSize.margins, topBarDelegate.width)
    implicitHeight: list.contentHeight + topBarDelegate.height

    Connections {
        target: map
        onHolded: presenter.setGlobalPoi(coordinate.latitude, coordinate.longitude, 0);
    }

    VehiclesListDisplayPresenter {
        id: presenter
        view: listDisplay
    }

    TopBarDelegate {
        id: topBarDelegate
        anchors.right: parent.right
    }

    SwarmWidget {
        id: swarmWidget
        anchors.top: topBarDelegate.bottom
        anchors.topMargin: controlSize.spacing
        anchors.right: parent.right
        anchors.rightMargin: controlSize.margins
        width: dashboardWidth
    }

    ListView {
        id: list
        anchors.top: swarmWidget.bottom
        anchors.topMargin: controlSize.spacing
        anchors.right: parent.right
        anchors.rightMargin: controlSize.margins
        width: dashboardWidth
        height: Math.min(parent.height - topBarDelegate.height - controlSize.spacing, contentHeight)
        spacing: controlSize.spacing
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

            width: parent.width - controlSize.shadowSize
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
