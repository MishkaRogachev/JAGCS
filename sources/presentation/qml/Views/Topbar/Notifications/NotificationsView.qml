import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: connection

    property int type: 0
    property int count: 0

    function logAdded() {
        count++;
    }

    NotificationsPresenter {
        id: presenter
        view: connection
        Component.onCompleted: initLog()
    }

    implicitWidth: sizings.controlBaseSize * 0.75
    implicitHeight: width
    radius: width / 2
    color: "transparent"
    border.width: 2
    border.color: {
        switch (type) {
        case LogMessage.Positive:
            return palette.positiveColor;
        case LogMessage.Warning:
            return palette.cautionColor;
        case LogMessage.Critical:
            return palette.dangerColor;
        case LogMessage.Common:
        default:
            return palette.textColor;
        }
    }

    Text {
        anchors.centerIn: parent
        color: parent.border.color
        font.pixelSize: sizings.fontPixelSize
        text: count
    }
}
