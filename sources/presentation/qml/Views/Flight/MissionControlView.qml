import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

ColumnLayout {
    id: root

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            text: qsTr("Item")
            font.bold: true
        }

        ComboBox {
            id: selectedItemBox
            Layout.fillWidth: true
            model: vehicle ? vehicle.missionItems : []
            currentIndex: -1
            enabled: vehicle
            onCurrentIndexChanged: {
                if (!vehicle || currentIndex === vehicle.currentItem) return;
                vehicle.commandJumpTo(currentIndex)
            }

            Connections {
                target: vehicle
                ignoreUnknownSignals: true
                onCurrentItemChanged: selectedItemBox.currentIndex = currentItem;
            }
        }
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Button {
            iconSource: "qrc:/icons/home.svg"
            onClicked: vehicle.commandReturn()
            enabled: vehicle
        }

        Button {
            iconSource: "qrc:/icons/restart.svg"
            onClicked: vehicle.commandRestart()
            enabled: vehicle
        }

        Button {
            iconSource: "qrc:/icons/play.svg"
            onClicked: vehicle.commandStart(selectedItemBox.currentIndex)
            enabled: vehicle
        }
    }
}
