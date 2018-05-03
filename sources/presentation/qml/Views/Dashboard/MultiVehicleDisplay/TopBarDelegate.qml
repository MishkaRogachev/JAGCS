import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopBarDelegateBase {
    id: topbarDelegate

    Controls.Button {
        flat: true
        text: dashboard.display.vehicles.showOffline ? qsTr("All vehicles") :
                                                       qsTr("Online vehicles")
        onClicked: dashboard.display.vehicles.setShowOffline(
                       !dashboard.display.vehicles.showOffline)
    }
}
