import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapCircle {
        center: position
        radius: hdopRadius
        color: industrial.colors.background
        border.width: 4
        border.color: industrial.colors.onSurface
        opacity: 0.3
        z: 250

        Behavior on center {
            CoordinateAnimation { duration: 200 }
        }
    }
}
