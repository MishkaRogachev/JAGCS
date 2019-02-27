import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import Industrial.Indicators 1.0 as Indicators

MapItemView {
    delegate: MapPolyline {
        line.width: 3
        line.color: Indicators.Theme.activeColor
        path: track
        smooth: true
        z: 100
    }
}
