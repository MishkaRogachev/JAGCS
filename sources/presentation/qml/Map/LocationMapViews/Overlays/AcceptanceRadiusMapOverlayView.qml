import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapCircle {
        center: itemCoordinate
        radius: itemAcceptanceRadius
        color: industrial.colors.highlight
        border.width: 0
        opacity: 0.3
        visible: itemCoordinate.isValid && itemAcceptanceRadius > 0 && itemVisible
        z: 50
    }
}
