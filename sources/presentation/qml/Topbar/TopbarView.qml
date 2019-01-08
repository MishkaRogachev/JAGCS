import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "Notification"
import "Clocks"

Rectangle {
    id: topbar

    color: industrial.colors.background
    height: industrial.baseSize * 0.75

    Controls.Shadow {
        source: parent
    }

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Math.max(tools.x + industrial.margins, burger.width)
        anchors.rightMargin: dashboard.topbarOffset
        spacing: industrial.spacing

        Behavior on anchors.rightMargin { PropertyAnimation { duration: 200 } }

        Repeater {
            model: [
                "Notification/NotificationButton.qml",
                "Connection/ConnectionButton.qml",
                "RadioStatus/RadioStatusButton.qml"
                // TODO: topbar plugins
            ]

            Loader { source: modelData }
        }

        ClocksButton {
            Layout.fillWidth: true
        }
    }
}
