import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "Overlays"

Map {
    id: root

    property var lineModel
    property var pointModel
    property var vehicleModel

    property bool vehicleVisible: true
    property bool missionPointsVisible: true
    property bool missionLinesVisible: true
    property bool trackVisible: true
    property bool hdopVisible: true

    property bool picking: false
    property bool trackingVehicle: false

    signal picked(var coordinate)

    implicitHeight: width

    plugin: Plugin {
        name: "osm"

        PluginParameter { name: "osm.useragent"; value: "JAGCS" }
        PluginParameter { name: "osm.mapping.custom.host"; value: "http://a.tile.openstreetmap.org/" }
        PluginParameter { name: "osm.mapping.cache.disk.size"; value: settings.value("Map/cacheSize", 0) }
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: settings.boolValue("Map/highdpiTiles", true) }
    }

    activeMapType: supportedMapTypes[settings.value("Map/activeMapType", 0)]
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    gesture.preventStealing: true
    copyrightsVisible: false

    MissionLineMapOverlayView {
        model: missionLinesVisible ? lineModel : 0
    }

    RadiusMapOverlayView {
        model: missionPointsVisible ? pointModel : 0
    }

    AcceptanceRadiusMapOverlayView {
        model: missionPointsVisible ? pointModel : 0
    }

    MissionPointMapOverlayView {
        model: missionPointsVisible ? pointModel : 0
    }

    VehicleMapOverlayView {
        model: vehicleVisible ? vehicleModel : 0
    }

    TrackMapOverlayView {
        model: trackVisible ? vehicleModel : 0
    }

    HdopRadiusMapOverlayView {
        model: hdopVisible ? vehicleModel : 0
    }

    MapQuickItem {
        id: pickHighlight
        anchorPoint.x: sourceItem.width / 2
        anchorPoint.y: sourceItem.height / 2
        z: 10000

        sourceItem: Rectangle {
            width: palette.controlBaseSize / 4
            height: width
            radius: width / 2
            color: palette.activeMissionColor
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: picking
        onClicked: {
            pickHighlight.coordinate = root.toCoordinate(Qt.point(mouseX, mouseY));
            pickHighlight.visible = true;
            root.picked(pickHighlight.coordinate);
        }
        cursorShape: picking ? Qt.CrossCursor : Qt.ArrowCursor
    }

    Component.onCompleted: {
        center = QtPositioning.coordinate(settings.value("Map/centerLatitude"),
                                          settings.value("Map/centerLongitude"));
        zoomLevel = settings.value("Map/zoomLevel");
    }

    Component.onDestruction: if (visible) saveViewport()

    onVisibleChanged: if (!visible) saveViewport()
    onTrackingVehicleChanged: setGesturesEnabled(!trackingVehicle)

    function saveViewport() {
        if (width == 0 || height == 0) return;

        settings.setValue("Map/centerLatitude", center.latitude);
        settings.setValue("Map/centerLongitude", center.longitude);
        settings.setValue("Map/zoomLevel", zoomLevel);
    }

    function setGesturesEnabled(enabled) {
        gesture.acceptedGestures = enabled ?
                    (MapGestureArea.PinchGesture | MapGestureArea.PanGesture |
                     MapGestureArea.FlickGesture) : MapGestureArea.PinchGesture
    }

    function dropPicker() {
        map.picking = false
        pickHighlight.visible = false;
    }
}
