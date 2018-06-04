import QtQuick 2.6
import JAGCS 1.0

import "../"

TopbarButton {
    id: button

    property bool connected: false
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    iconSource: connection.connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
    iconColor: connection.connected ? customPalette.textColor : customPalette.dangerColor
    tipText: qsTr("Connection")

    onClicked: info.visible ? info.close() : info.open()

    ConnectionPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateStatus()
    }

    ConnectionInfo {
        id: info
        y: parent.height + sizings.margins
    }
}
