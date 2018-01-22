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

            SplineSeries {
                axisX : ValueAxis {
                    min: 0 //chartModel.xMin
                    max: 1000 //chartModel.xMax
                }

                axisY : ValueAxis {
                    min: 0
                    max: 1
                }

                VXYModelMapper {
                    xColumn: 0
                    yColumn: 1
                    model: vibration
                }

                VXYModelMapper {
                    xColumn: 0
                    yColumn: 2
                    model: vibration
                }

                VXYModelMapper {
                    xColumn: 0
                    yColumn: 3
                    model: vibration
                }
            }
        }
    }
}
