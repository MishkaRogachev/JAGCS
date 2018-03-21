import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtCharts 2.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    padding: 0

    RowLayout {
        anchors.centerIn: parent
        width: parent.width - sizings.padding * 2
        spacing: sizings.spacing

        Controls.Label {
            text: qsTr("EKF")
        }

        Indicators.EkfIndicator {
            bars: [
                vehicle.ekf.velocityVariance,
                vehicle.ekf.verticalVariance,
                vehicle.ekf.horizontVariance,
                vehicle.ekf.compassVariance,
                vehicle.ekf.terrainAltitudeVariance
            ]
        }

        Controls.Label {
            text: qsTr("Vib.")
        }

        Indicators.MiniPlot {
            id: plot
            Layout.fillWidth: true
            Layout.minimumHeight: sizings.controlBaseSize * 1.5
            Layout.fillHeight: true
            // FIXME: segfault on destruction
            ValueAxis {
                id: timeAxis
                visible: false
                min: vehicle.ahrs.vibration.minTime
                max: vehicle.ahrs.vibration.maxTime
            }

            ValueAxis {
                id: valueAxis
                visible: false
                max: vehicle.ahrs.vibration.maxValue
            }

            LineSeries {
                axisX: timeAxis
                axisY: valueAxis
                color: customPalette.positiveColor

                VXYModelMapper {
                    xColumn: 0
                    yColumn: 1
                    model: vehicle.ahrs.vibration
                }
            }

            LineSeries {
                axisX: timeAxis
                axisY: valueAxis
                color: customPalette.cautionColor

                VXYModelMapper {
                    xColumn: 0
                    yColumn: 2
                    model: vehicle.ahrs.vibration
                }
            }

            LineSeries {
                axisX: timeAxis
                axisY: valueAxis
                color: customPalette.dangerColor

                VXYModelMapper {
                    xColumn: 0
                    yColumn: 3
                    model: vehicle.ahrs.vibration
                }
            }
        }
    }
}
