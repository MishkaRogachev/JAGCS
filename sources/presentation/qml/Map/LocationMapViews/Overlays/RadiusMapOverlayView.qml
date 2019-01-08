import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapCircle {
        center: itemCoordinate
        radius: itemRadius
        color: "transparent"
        border.width: 4
        border.color: industrial.colors.highlight
        visible: itemCoordinate.isValid && itemRadius > 0 && itemVisible
        z: 75
    }
}
