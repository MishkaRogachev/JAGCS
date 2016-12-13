import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property alias missionNames: missionBox.model
    property var missionItems

    signal missionSelected(string name)
    signal addMissionItem()
    signal removeMissionItem(QtObject item)

    MissionMapView {
        id: map
        objectName: "map"
        anchors.fill: parent
    }

    ColumnLayout {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 360
        anchors.left: parent.left
        anchors.margins: 7

        RowLayout {

            ComboBox {
                id: missionBox
                Layout.fillWidth: true
                onCurrentTextChanged: missionSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
            }
        }

        Flickable {
            width: parent.width
            Layout.fillHeight: true
            clip: true
            contentWidth: column.width
            contentHeight: column.height

            ColumnLayout {
                id: column
                width: parent.width
                anchors.centerIn: parent
                spacing: 8

                Repeater {
                    model: missionItems

                    MissionItemView {
                        Layout.fillWidth: true
                        coordinate: modelData.coordinate
                        onCoordinateChanged: modelData.setCoordinate(coordinate)
                        onRemove: removeMissionItem(modelData)
                    }
                }
            }
        }

        Button {
            id: addButton
            Layout.fillWidth: true
            text: qsTr("Add Item")
            iconSource: "qrc:/icons/add.svg"
            enabled: missionBox.currentIndex > -1
            onClicked: addMissionItem()
        }
    }
}
