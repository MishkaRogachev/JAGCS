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
        if (minDistance > distance) minDistance = distance * 1.1;
        if (minAltitude > altitude) minAltitude = altitude * 1.1;
        if (maxDistance < distance) maxDistance = distance * 1.1;
        if (maxAltitude < altitude) maxAltitude = altitude * 1.1;
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
        minDistance = 0;
        minAltitude = 0;
        maxDistance = 0;
        maxAltitude = 0;
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
            id: paths
            axisX: distanceAxis
            axisY: altitudeAxis
            color: palette.missionColor
            width: 2
        }

        ScatterSeries {
            id: waypoints
            axisX: distanceAxis
            axisY: altitudeAxis
            color: palette.missionColor
            // TODO: border color selected
        }
    }
}
