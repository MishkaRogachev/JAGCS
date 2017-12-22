import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

RowLayout {
    id: radioStatus

    property alias rssi: rssiItem.rssi
    property alias remoteRssi: remoteRssiItem.rssi

    spacing: sizings.spacing

    RadioStatusPresenter {
        id: presenter
        view: radioStatus
        Component.onCompleted: updateParameters()
    }

    Indicators.RssiIndicator {
        id: rssiItem
    }

    Controls.Label {
        text: qsTr("RSSI: ") + rssi.toFixed(1) + qsTr(" dBm")
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
    }

    Indicators.RssiIndicator {
        id: remoteRssiItem
    }

    Controls.Label {
        text: qsTr("Rem. RSSI: ") + remoteRssi.toFixed(1) + qsTr(" dBm")
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
    }
}
