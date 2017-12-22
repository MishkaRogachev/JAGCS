import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

RowLayout {
    id: connection

    property bool connected: false
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    spacing: sizings.spacing

    ConnectionPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateStatus()
    }

    Controls.Button {
        iconSource: connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        iconColor: connected ? palette.textColor : palette.dangerColor
        flat: true
        onClicked: presenter.setConnected(!connected)
    }

    Controls.ContentItem {
        iconSource: "qrc:/icons/up.svg"
        text: bytesSent.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
    }

    Controls.ContentItem {
        iconSource: "qrc:/icons/down.svg"
        text: bytesRecv.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
    }
}
