import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators

RowLayout {
    id: row

    property bool recv: false
    property bool sent: false

    spacing: sizings.spacing

    Connections {
        target: presenter

        onRecv: recv = true
        onSent: sent = true
    }

    Timer {
        running: sent
        interval: 100
        onTriggered: sent = false
    }

    Timer {
        running: recv
        interval: 100
        onTriggered: recv = false
    }



    Indicators.Led {
        color: recv ? customPalette.positiveColor : customPalette.sunkenColor
    }

    Controls.Label {
        text: qsTr("Recv") + ": " + presenter.bytesRecv.toFixed(1) + " " + qsTr("B/s")
        horizontalAlignment: Text.AlignHCenter
        color: customPalette.positiveColor
        Layout.fillWidth: true
    }

    Indicators.Led {
        color: sent ? customPalette.skyColor : customPalette.sunkenColor
    }

    Controls.Label {
        text: qsTr("Sent") + ": " + presenter.bytesSent.toFixed(1) + " " + qsTr("B/s")
        horizontalAlignment: Text.AlignHCenter
        color: customPalette.skyColor
        Layout.fillWidth: true
    }
}
