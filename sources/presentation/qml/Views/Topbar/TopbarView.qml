import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "Notification"
import "Clocks"

Rectangle {
    id: topbar

    color: customPalette.backgroundColor
    height: sizings.controlBaseSize * 0.75

    Controls.Shadow {
        source: parent
    }

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: tools.x + tools.width + sizings.margins
        anchors.rightMargin: sizings.margins
        spacing: sizings.spacing

        NotificationButton {
            id: notification
        }

        ClocksButton {
            Layout.fillWidth: true
        }

        Repeater {
            model: [
                "RadioStatus/RadioStatusButton.qml",
                "Connection/ConnectionButton.qml"
            ]

            Loader { source: modelData }
        }
    }
}
