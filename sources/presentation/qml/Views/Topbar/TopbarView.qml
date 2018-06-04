import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "RadioStatus"
import "Connection"

Rectangle {
    id: topbar

    color: customPalette.backgroundColor
    height: sizings.controlBaseSize

    Controls.Shadow {
        source: parent
    }

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.right: parent.right
        anchors.rightMargin: dashboard.width
        height: parent.height
        spacing: sizings.spacing
        clip: true

        ConnectionView {
            id: connection
        }

        RadioStatusView {
            id: radioStatus
        }
    }
}
