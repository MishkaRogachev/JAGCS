import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

Controls.Pane {
    id: root

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Indicators.StateIndicator {
            state: vehicleState
        }

        Indicators.EkfIndicator {
            bars: [ velocityVariance, verticalVariance, horizontVariance,
                compassVariance, terrainAltitudeVariance ]
        }

        // TODO: vibration
    }
}
