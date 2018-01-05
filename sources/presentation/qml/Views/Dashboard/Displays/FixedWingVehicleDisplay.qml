import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators
import "../CommandControls" as CommandControls

BaseVehicleDisplay {
    id: vehicleDisplay

    property bool ahrsOperational: false
}
