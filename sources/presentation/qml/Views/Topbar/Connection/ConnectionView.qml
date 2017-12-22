import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

RowLayout {
    id: connection

    property bool connected: false
    property real sended: 0.0
    property real received: 0.0

    spacing: sizings.spacing

//    ConnectionPresenter {
//        id: presenter
//        view: connection
//        //Component.onCompleted:
//    }

    Controls.ColoredIcon {
        source: connected ? "qrc:/icons/connect.svg" : "qrc:/icons/disconnect.svg"
        color: connected ? palette.textColor : palette.dangerColor
    }

    Controls.ContentItem {
        iconSource: "qrc:/icons/up.svg"
        text: sended.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
    }

    Controls.ContentItem {
        iconSource: "qrc:/icons/down.svg"
        text: received.toFixed(1) + " " + qsTr("B/s")
        font.pixelSize: sizings.fontPixelSize * 0.6
        font.bold: true
    }
}
