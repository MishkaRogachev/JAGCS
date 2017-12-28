import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: connection

    property bool connected: false
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    spacing: 0

    ConnectionPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateStatus()
    }

    Controls.ContentItem {
        iconSource: "qrc:/icons/up.svg"
        text: bytesSent.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.fontPixelSize * 0.5
        font.bold: true
    }

    Controls.ContentItem {
        iconSource: "qrc:/icons/down.svg"
        text: bytesRecv.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.fontPixelSize * 0.5
        font.bold: true
    }
}
