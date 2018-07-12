import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: connection

    property bool connected: false
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    property bool sent: false
    property bool recv: false

    onClicked: info.visible ? info.close() : info.open()

    ConnectionPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateStatus()
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

    Controls.ColoredIcon {
        anchors.centerIn: parent
        width: parent.height * 0.8
        height: parent.height * 0.8
        source: connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        color: connected ? customPalette.textColor : customPalette.dangerColor
    }

    ConnectionInfo {
        id: info
        y: parent.height + sizings.margins
    }
}
