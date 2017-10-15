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
    property alias pickerCoordinate: picker.coordinate
    property alias pickerVisible: picker.visible

    property bool trackingVehicle: false

    property int mapPlugin: settings.value("Map/plugin")

    signal picked(var coordinate)

    Plugin {
        id: osm
        name: "osm"

        PluginParameter { name: "osm.useragent"; value: "JAGCS" }
        PluginParameter { name: "osm.mapping.custom.host"; value: "http://a.tile.openstreetmap.org/" }
        PluginParameter { name: "osm.mapping.cache.disk.size"; value: settings.value("Map/cacheSize", 0) }
        PluginParameter { name: "osm.mapping.highdpi_tiles"; value: settings.boolValue("Map/highdpiTiles", true) }
    }

    Plugin {
        id: mapBoxGl
        name: "mapboxgl"

        PluginParameter { name: "mapboxgl.mapping.cache.size"; value: settings.value("Map/cacheSize", 0) }
    }

    plugin: mapPlugin ? mapBoxGl : osm // TODO: different map views for map type
    implicitHeight: width
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

    TargetPointOverlayView {
        model: vehicleVisible ? vehicleModel : 0
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

    MapPicker {
        id: picker
        z: 10000
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        enabled: picking
        onClicked: root.picked(root.toCoordinate(Qt.point(mouseX, mouseY)));
        cursorShape: picking ? Qt.CrossCursor : Qt.ArrowCursor
    }

    Component.onCompleted: {
        center = QtPositioning.coordinate(settings.value("Map/centerLatitude"),
                                          settings.value("Map/centerLongitude"));
        zoomLevel = settings.value("Map/zoomLevel");
        bearing = settings.value("Map/bearing");
    }

    Component.onDestruction: if (visible) saveViewport()
    onVisibleChanged: if (!visible) saveViewport()
    onTrackingVehicleChanged: setGesturesEnabled(!trackingVehicle)

    function saveViewport() {
        if (width == 0 || height == 0) return;

        settings.setValue("Map/centerLatitude", center.latitude);
        settings.setValue("Map/centerLongitude", center.longitude);
        settings.setValue("Map/zoomLevel", zoomLevel);
        settings.setValue("Map/bearing", bearing);
    }

    function setGesturesEnabled(enabled) {
        gesture.acceptedGestures = enabled ?
                    (MapGestureArea.PinchGesture | MapGestureArea.PanGesture |
                     MapGestureArea.FlickGesture | MapGestureArea.RotationGesture) :
                    MapGestureArea.PinchGesture
    }
}
