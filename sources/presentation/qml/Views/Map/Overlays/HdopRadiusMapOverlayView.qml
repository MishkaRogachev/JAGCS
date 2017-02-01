import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

MapItemView {
    delegate: MapCircle {
        center: position
        radius: hdopRadius
        color: palette.backgroundColor
        border.width: 4
        border.color: palette.textColor
        opacity: 0.3

        Behavior on center {
            CoordinateAnimation { duration: 200 }
        }
    }
}
