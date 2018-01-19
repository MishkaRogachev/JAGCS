import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Indicators.EkfIndicator {
            bars: [ velocityVariance, verticalVariance, horizontVariance,
                compassVariance, terrainAltitudeVariance ]
        }

        Indicators.MiniPlot {
            id: plot
            Layout.fillWidth: true
            Layout.minimumHeight: sizings.controlBaseSize * 1.5
            Layout.fillHeight: true

            LineSeries {
                id: xSeries
                name: "X"
                axisX: plot.timeAxis
                axisY: plot.valueAxis
                width: 2
                color: palette.positiveColor
            }

            LineSeries {
                id: ySeries
                name: "Y"
                axisX: plot.timeAxis
                axisY: plot.valueAxis
                width: 2
                color: palette.cautionColor
            }

            LineSeries {
                id: zSeries
                name: "Z"
                axisX: plot.timeAxis
                axisY: plot.valueAxis
                width: 2
                color: palette.dangerColor
            }

            Connections {
                target: vehicleDisplay

                onVibrationChanged: {
                    xSeries.append(plot.time, vibration.x);
                    ySeries.append(plot.time, vibration.y);
                    zSeries.append(plot.time, vibration.z);

                    if (plot.time > 100)
                    {

                        xSeries.removePoints(0, 1);
                        ySeries.removePoints(0, 1);
                        zSeries.removePoints(0, 1);
                    }

                    if (vibration.x > plot.topValue) plot.topValue = vibration.x;
                    if (vibration.y > plot.topValue) plot.topValue = vibration.y;
                    if (vibration.z > plot.topValue) plot.topValue = vibration.z;

                    plot.time++;
                }
            }
        }
    }
}
