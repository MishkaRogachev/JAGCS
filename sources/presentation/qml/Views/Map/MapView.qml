import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "Overlays"

Map {
    id: root

    property var lineModel
    property var pointModel
    property var vehicleModel

    signal saveMapViewport()

    plugin: Plugin { name: "osm" }
    gesture.flickDeceleration: 3000
    gesture.enabled: true
    activeMapType: supportedMapTypes[5] // TerrainMapType
    copyrightsVisible: false

    Behavior on center {
        CoordinateAnimation {
            duration: 200
            easing.type: Easing.InOutQuad
        }
    }

    MissionLineMapOverlayView {
        model: lineModel
    }

    RadiusMapOverlayView {
        model: pointModel
    }

    AcceptanceRadiusMapOverlayView {
        model: pointModel
    }

    MissionPointMapOverlayView {
        model: pointModel
    }

    VehicleMapOverlayView {
        model: vehicleModel
    }

    Component.onDestruction: saveMapViewport()
}
