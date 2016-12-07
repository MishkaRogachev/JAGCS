import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property var missionNames
    property var missionItems

    signal missionSelected(string name)

    MissionMapView {
        objectName: "map"
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 7

        RowLayout {
            ComboBox {
                model: missionNames
                onCurrentTextChanged: missionSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            anchors.centerIn: parent
            spacing: 8

            Repeater {
                id: repeater
                model: missionItems

                MissionItemView {
                    Layout.fillWidth: true
                    coordinate: modelData.coordinate
                }
            }
        }

        Button {
            Layout.fillWidth: true
            text: qsTr("Add Item")
            iconSource: "qrc:/icons/add.svg"
        }
    }
}
