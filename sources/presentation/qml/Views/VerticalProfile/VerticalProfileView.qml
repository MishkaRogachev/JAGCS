import QtQuick 2.6
import QtCharts 2.0

import "qrc:/Controls" as Controls

Item {
    id: root

    property real minDistance: 0
    property real maxDistance: 0
    property real minAltitude: 0
    property real maxAltitude: 0

    function appendWaypoint(distance, altitude) {
        waypoints.append(distance, altitude);
        paths.append(distance, altitude);
    }

    function insertWaypoint(index, distance, altitude) {
        waypoints.append(index, distance, altitude);
        paths.append(index, distance, altitude);
    }

    function removeWaypoint(index) {
        waypoints.remove(index);
        paths.remove(index);
    }

    function clearWaypoints() {
        waypoints.clear();
        paths.clear();
    }

    ChartView {
        anchors.fill: parent
        antialiasing: true
        animationOptions: ChartView.SeriesAnimations
        backgroundColor: "transparent"
        legend.visible: false

        ValueAxis {
            id: distanceAxis
            min: minDistance - (maxDistance - minDistance) * 0.01
            max: maxDistance + (maxDistance - minDistance) * 0.01
            labelsColor: customPalette.textColor
        }

        ValueAxis {
            id: altitudeAxis
            min: minAltitude - (maxAltitude - minAltitude) * 0.1
            max: maxAltitude + (maxAltitude - minAltitude) * 0.1
            labelsColor: customPalette.textColor
        }

        LineSeries {
            id: paths
            axisX: distanceAxis
            axisY: altitudeAxis
            color: customPalette.missionColor
            width: 2
        }

        ScatterSeries {
            id: waypoints
            axisX: distanceAxis
            axisY: altitudeAxis
            color: customPalette.missionColor
            // TODO: border color selected
        }
    }
}
