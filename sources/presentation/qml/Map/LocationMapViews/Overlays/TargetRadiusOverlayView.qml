import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapCircle {
        center: targetPosition
        radius: 50
        color: "#FFFFFF" // FIXME: MapBox GL does not draw transparent circles
        border.width: 4
        border.color: industrial.colors.activeMissionColor
        z: 50
    }
}
