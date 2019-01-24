import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapCircle {
        center: position
        radius: hdopRadius
        color: customPalette.backgroundColor
        border.width: 4
        border.color: customPalette.textColor
        opacity: 0.3
        z: 10

        Behavior on center {
            CoordinateAnimation { duration: 200 }
        }
    }
}
