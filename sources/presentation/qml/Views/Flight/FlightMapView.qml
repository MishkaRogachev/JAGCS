import QtQuick 2.6

import "../Map"
import "../Map/Overlays"

MapView {
    id: root

    TrackMapOverlayView {
        model: vehicleModel
    }
}
