import QtQuick 2.6
import QtCharts 2.0
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: verticalProfile

    property alias minDistance: distanceAxis.min
    property alias maxDistance: distanceAxis.max
    property alias minAltitude: altitudeAxis.min
    property alias maxAltitude: altitudeAxis.max

    function setMission(missionId) { presenter.setMission(missionId); }

    function appendWaypoint(distance, altitude) { series.append(distance, altitude); }
    function removeWaypoint(index) { series.remove(index); }
    function clearWaypoints() { series.clear(); }

    padding: 0

    VerticalProfilePresenter {
        id: presenter
        view: verticalProfile
    }

    ChartView {
        anchors.fill: parent
        antialiasing: true
        animationOptions: ChartView.NoAnimation
        backgroundColor: "transparent"
        legend.visible: false

        ValueAxis {
            id: distanceAxis
            labelsColor: industrial.colors.onSurface
            labelsFont.pixelSize: industrial.auxFontSize
            labelsFont.bold: true
        }

        ValueAxis {
            id: altitudeAxis
            labelsColor: industrial.colors.onSurface
            labelsFont.pixelSize: industrial.auxFontSize
            labelsFont.bold: true
        }

        AreaSeries {
            color: industrial.colors.highlight
            borderColor: industrial.colors.highlight
            borderWidth: 2
            opacity: 0.33
            axisX: distanceAxis
            axisY: altitudeAxis
            upperSeries: LineSeries {
                id: series
                color: industrial.colors.highlight
                width: 2
            }
        }
    }
}
