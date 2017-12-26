import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
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

    flat: true
    iconSource: "qrc:/icons/notify.svg"
    iconColor: {
        if (count == 0) return palette.sunkenColor;

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
        color: parent.iconColor
        font.pixelSize: sizings.fontPixelSize * 0.6
        text: count > 0 ? count : "!"
    }
}
