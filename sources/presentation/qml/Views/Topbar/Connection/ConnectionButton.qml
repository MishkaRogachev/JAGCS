import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../"

TopbarButton {
    id: connection

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
        anchors.centerIn: parent
        source: connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        color: connected ? customPalette.textColor : customPalette.dangerColor
    }

    ConnectionInfo {
        id: info
        x: parent.width - width
        y: parent.height + sizings.margins
    }
}
