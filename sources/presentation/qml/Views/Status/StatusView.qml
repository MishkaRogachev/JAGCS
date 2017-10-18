import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../Logbook"

Controls.ToolBar {
    id: root

    signal setMode(int mode)
    signal quit()

    RowLayout {
        anchors.fill: parent
        spacing: palette.spacing

        Image {
            source: "qrc:/icons/jagcs.svg"
            anchors.verticalCenter: parent.verticalCenter
            sourceSize.width: palette.controlBaseSize
            sourceSize.height: palette.controlBaseSize
        }

        Controls.Label {
            text: "JAGCS"
        }

        RadioStatusView {
            objectName: "radio"
            anchors.verticalCenter: parent.verticalCenter
        }

        LogbookView {
            objectName: "logbook"
            Layout.fillWidth: true
            implicitHeight: root.height
        }

        RowLayout {
            spacing: 1

            StatusModeButton {
                mode: MainPresenter.Control
                iconSource: "qrc:/icons/flight.svg"
                anchors.verticalCenter: parent.verticalCenter
            }

            StatusModeButton {
                mode: MainPresenter.Planning
                iconSource: "qrc:/icons/map-marker.svg"
                anchors.verticalCenter: parent.verticalCenter
            }

            StatusModeButton {
                mode: MainPresenter.Settings
                iconSource: "qrc:/icons/settings.svg"
                anchors.verticalCenter: parent.verticalCenter
            }

            Controls.Button {
                iconSource: "qrc:/icons/quit.svg"
                iconColor: palette.dangerColor
                anchors.verticalCenter: parent.verticalCenter
                onClicked: quit()
            }
        }
    }
}
