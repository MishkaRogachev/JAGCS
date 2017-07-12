import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0

import "qrc:/Controls" as Controls

ChartView {
    id: root

    property real minDistance: 0
    property real maxDistance: 1
    property real minAltitude: 0
    property real maxAltitude: 1

    function appendWaypoint(distance, altitude) {
        waypoints.append(distance, altitude);
    }

    function insertWaypoint(index, distance, altitude) {
        waypoints.append(index, distance, altitude);
    }

    function removeWaypoint(index) {
        waypoints.remove(index);
    }

    function clearWaypoints() {
        waypoints.clear();
    }

    antialiasing: true
    animationOptions: ChartView.SeriesAnimations
    backgroundColor: "transparent"
    legend.visible: false

    ValueAxis {
        id: distanceAxis
        min: minDistance
        max: maxDistance
        labelsColor: palette.textColor
    }

    ValueAxis {
        id: altitudeAxis
        min: minAltitude
        max: maxAltitude
        labelsColor: palette.textColor
    }

    LineSeries {
        id: waypoints
        axisX: distanceAxis
        axisY: altitudeAxis
        color: palette.missionColor
        width: 2
    }
}
