import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: button

    property bool connected: false
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    onClicked: info.visible ? info.close() : info.open()

    ConnectionPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateStatus()
    }

    Controls.ColoredIcon {
        anchors.fill: parent
        source: connection.connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        color: connection.connected ? customPalette.textColor : customPalette.dangerColor
    }

    ConnectionInfo {
        id: info
        y: parent.height + sizings.margins
    }
}
