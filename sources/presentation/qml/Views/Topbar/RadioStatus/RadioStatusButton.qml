import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Indicators" as Indicators
import "../"

TopbarButton {
    id: button

    property alias rssi: rssiItem.rssi
    property alias remoteRssi: remoteRssiItem.rssi

    implicitWidth: row.width

    onClicked: info.visible ? info.close() : info.open()

    RadioStatusPresenter {
        id: presenter
        view: radioStatus
        Component.onCompleted: updateParameters()
    }

    Row {
        id: row
        anchors.centerIn: parent
        spacing: sizings.spacing

        Indicators.RssiIndicator {
            id: rssiItem
            height: button.height
        }

        Indicators.RssiIndicator {
            id: remoteRssiItem
            height: button.height
        }
    }

    RadioStatusInfo {
        id: info
        y: parent.height + sizings.margins
    }
}
