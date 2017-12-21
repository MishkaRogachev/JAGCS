import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.Pane {
    id: baseDisplay

    property int vehicleId: 0
    property string vehicleName
    property bool online: false
}
