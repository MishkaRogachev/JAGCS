import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

BaseDisplay {
    id: vehicleDisplay

    property alias armed: ai.armed

    property bool ahrsEnabled: false
    property bool ahrsOperational: false
    property alias pitch: ai.pitch
    property alias roll: ai.roll

    property bool satelliteEnabled: false
    property bool satelliteOperational: false

    property bool pitotEnabled: false
    property bool pitotOperational: false
    property real indicatedAirspeed: 0

    property bool barometricEnabled: false
    property bool barometricOperational: false
    property int barometricAltitude: 0

    property bool rangefinderEnabled: false
    property bool rangefinderOperational: false

    property int homeAltitude: 0

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")

    RowLayout {
        Indicators.ArtificialHorizon {
            id: ai
            implicitWidth: vehicleDisplay.width / 6
            implicitHeight: width * 1.5
            enabled: ahrsEnabled
            operational: ahrsOperational
            rollInverted: vehicleDisplay.rollInverted
        }
    }
}
