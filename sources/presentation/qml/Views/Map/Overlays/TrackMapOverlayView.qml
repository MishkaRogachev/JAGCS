import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapPolyline {
        line.width: 4
        line.color: palette.trackColor
        path: track
        smooth: true
    }
}
