import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

RowLayout {
    id: root

    property alias rssi: rssiItem.rssi
    property alias remoteRssi: remoteRssiItem.rssi

    Indicators.RssiIndicator {
        id: rssiItem
    }

    Controls.Label {
        text: qsTr("RSSI: ") + rssi.toFixed(1) + qsTr(" dBm")
        font.pixelSize: palette.fontPixelSize * 0.75
    }

    Indicators.RssiIndicator {
        id: remoteRssiItem
    }

    Controls.Label {
        text: qsTr("Rem. RSSI: ") + remoteRssi.toFixed(1) + qsTr(" dBm")
        font.pixelSize: palette.fontPixelSize * 0.75
    }
}
