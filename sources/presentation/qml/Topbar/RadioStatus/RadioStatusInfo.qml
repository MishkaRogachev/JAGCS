import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Popup {
    id: info

    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    ColumnLayout {
        spacing: industrial.spacing

        Controls.Label {
            text: qsTr("RSSI:") + " " + rssi.toFixed(1) + " " + qsTr("dBm")
            font.pixelSize: industrial.fontSize * 0.75
            font.bold: true
        }

        Controls.Label {
            text: qsTr("Rem. RSSI:") + " " + remoteRssi.toFixed(1) + " " + qsTr("dBm")
            font.pixelSize: industrial.fontSize * 0.75
            font.bold: true
        }
    }
}
