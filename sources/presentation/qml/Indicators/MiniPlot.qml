import QtQuick 2.6
import QtCharts 2.0
import JAGCS 1.0

import "../Controls" as Controls

ChartView {
    id: chart

    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    backgroundColor: customPalette.sunkenColor
    legend.visible: false
    margins.top: 0
    margins.bottom: 0
    margins.left: 0
    margins.right: 0
    antialiasing: true
}
