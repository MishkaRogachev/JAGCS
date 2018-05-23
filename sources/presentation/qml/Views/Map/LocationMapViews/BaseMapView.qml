import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import "../"
import "Overlays"

Map {
    id: map

    property var lineModel
    property var pointModel
    property var vehicleModel

    property bool vehicleVisible: true
    property bool missionPointsVisible: true
    property bool missionLinesVisible: true
    property bool trackVisible: true
    property bool hdopVisible: true

    property int trackingVehicleId: 0
    property bool trackYaw: false

    property int selectedItemId: 0

    property int activeMapTypeIndex: 0

    signal selectItem(int missionId, int itemId)
    signal itemDragged(int itemId, var coordinate);

    activeMapType: supportedMapTypes[activeMapTypeIndex]
    implicitWidth: height
    implicitHeight: width
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    gesture.preventStealing: true
    copyrightsVisible: false

    LocationMapPresenter {
        id: presenter
        view: map
    }

    MissionLineMapOverlayView { model: missionLinesVisible ? lineModel : 0 }
    RadiusMapOverlayView { model: missionPointsVisible ? pointModel : 0 }
    AcceptanceRadiusMapOverlayView { model: missionPointsVisible ? pointModel : 0 }
    MissionPointMapOverlayView { model: missionPointsVisible ? pointModel : 0 }
    TargetPointOverlayView { model: vehicleVisible ? vehicleModel : 0 }
    VehicleMapOverlayView { model: vehicleVisible ? vehicleModel : 0 }
    TrackMapOverlayView { model: trackVisible ? vehicleModel : 0 }
    HdopRadiusMapOverlayView { model: hdopVisible ? vehicleModel : 0 }

    Component.onCompleted: {
        center = QtPositioning.coordinate(settings.value("Map/centerLatitude"),
                                          settings.value("Map/centerLongitude"));
        zoomLevel = settings.value("Map/zoomLevel");
        bearing = settings.value("Map/bearing");
        tilt = settings.value("Map/tilt");

        updateGestures(true);
    }

    Component.onDestruction: if (visible) saveViewport()
    onVisibleChanged: if (!visible) saveViewport()

    onTrackingVehicleIdChanged: updateGestures()
    onTrackYawChanged: updateGestures()

    function saveViewport() {
        if (width == 0 || height == 0) return;

        settings.setValue("Map/centerLatitude", center.latitude);
        settings.setValue("Map/centerLongitude", center.longitude);
        settings.setValue("Map/zoomLevel", zoomLevel);
        settings.setValue("Map/bearing", bearing);
        settings.setValue("Map/tilt", tilt);
    }

    function updateGestures(enabled) {
        gesture.acceptedGestures = trackingVehicleId == 0 ?
                    (MapGestureArea.PinchGesture | MapGestureArea.PanGesture |
                     MapGestureArea.FlickGesture | MapGestureArea.RotationGesture |
                     MapGestureArea.TiltGesture)
                  : (trackYaw ?
                         MapGestureArea.PinchGesture | MapGestureArea.TiltGesture :
                         MapGestureArea.PinchGesture | MapGestureArea.RotationGesture |
                         MapGestureArea.TiltGesture)
    }
}
