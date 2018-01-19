import QtQuick 2.6
import QtCharts 2.0
import JAGCS 1.0

import "../Controls" as Controls

ChartView { // TODO: HXYModelMapper
    id: chart

    property int time: 0
    property real topValue: 0.0

    property ValueAxis timeAxis: ValueAxis {
        visible: false
        max: time
    }

     property ValueAxis valueAxis: ValueAxis {
        visible: false
        max: topValue
    }

    backgroundColor: palette.sunkenColor
   // legend.labelColor: palette.textColor
    //legend.alignment: Qt.AlignLeft
    legend.visible: false
    margins.top: 0
    margins.bottom: 0
    margins.left: 0
    margins.right: 0
    antialiasing: true
}
