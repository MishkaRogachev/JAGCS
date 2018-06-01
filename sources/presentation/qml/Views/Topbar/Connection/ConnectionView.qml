import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: connection

    property bool connected: false
    property real bytesRecv: 0.0
    property real bytesSent: 0.0

    implicitWidth: sizings.controlBaseSize * 2
    implicitHeight: sizings.controlBaseSize

    ConnectionPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateStatus()
    }

    Controls.ContentItem {
        anchors.top: parent.top
        iconSource: "qrc:/icons/up.svg"
        text: bytesSent.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.primaryFontSize * 0.5
        font.bold: true
        horizontalAlignment: Text.AlignLeft
        width: parent.width
        height: connection.height / 2
    }

    Controls.ContentItem {
        anchors.bottom: parent.bottom
        iconSource: "qrc:/icons/down.svg"
        text: bytesRecv.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.primaryFontSize * 0.5
        font.bold: true
        horizontalAlignment: Text.AlignLeft
        width: parent.width
        height: connection.height / 2
    }
}
