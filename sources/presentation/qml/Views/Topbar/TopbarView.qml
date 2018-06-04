import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "RadioStatus"
import "Connection"

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
        anchors.leftMargin: burger.width
        spacing: sizings.spacing

        ConnectionButton {
            id: connection
        }

//        ConnectionView {
//            id: connection
//        }

//        RadioStatusView {
//            id: radioStatus
//        }
    }
}
