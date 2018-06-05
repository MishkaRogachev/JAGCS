import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

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
        anchors.leftMargin: burger.width
        anchors.rightMargin: sizings.margins
        spacing: sizings.spacing

        ClocksButton {
            Layout.fillWidth: true
        }

        Repeater {
            model: [
                "Connection/ConnectionButton.qml",
                "RadioStatus/RadioStatusButton.qml"
            ]

            Loader { source: modelData }
        }
    }
}
