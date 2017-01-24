import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property QtObject helper

    property alias missionNames: missionBox.model
    property alias vehicleNames: vehicleBox.model

    property int currentCount: 0
    property int totalCount: 0

    property var missionItems: []

    signal missionSelected(string name)
    signal addMission()
    signal removeMission()

    signal vehicleSelected(string name)
    signal downloadMission()
    signal uploadMission()

    signal addMissionItem()
    signal removeMissionItem(QtObject item)

    padding: 0

    MissionMapView {
        id: map
        objectName: "map"
        anchors.top: topbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: sidebar.right
        anchors.right: parent.right
    }

    Item {
        id: topbar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 6
        anchors.rightMargin: 6
        height: palette.controlBaseSize + 12

        RowLayout {
            anchors.fill: parent

            ComboBox {
                id: missionBox
                Layout.fillWidth: true
                onModelChanged: {
                    currentIndex = -1;
                    currentIndex = count - 1;
                }
                onCurrentTextChanged: missionSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/add.svg"
                onClicked: addMission()
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
                enabled: missionBox.currentIndex != -1
                onClicked: removeMission()
            }

            ComboBox {
                id: vehicleBox
                Layout.fillWidth: true
                onModelChanged: {
                    currentIndex = -1;
                    currentIndex = count - 1;
                }
                onCurrentTextChanged: vehicleSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
                enabled: missionBox.currentIndex != -1 && vehicleBox.currentIndex != -1
                onClicked: downloadMission()
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
                enabled: missionBox.currentIndex != -1 && vehicleBox.currentIndex != -1
                onClicked: uploadMission()
            }

            ProgressBar {
                Layout.fillWidth: true
                from: 0
                to: totalCount
                value: currentCount
            }
        }
    }

    Flickable {
        id: sidebar
        anchors.top: topbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: contentWidth
        clip: true
        contentWidth: column.width
        contentHeight: column.height

        ScrollBar.vertical: ScrollBar {}

        ColumnLayout {
            id: column

            Repeater {
                id: repeater
                model: missionItems
                onModelChanged: {
                    if (column.height > sidebar.height)
                        sidebar.contentY = column.height - sidebar.height;
                }

                MissionItemView {
                    item: modelData
                    Layout.preferredWidth: column.width
                    avalibleCommands: helper ? helper.avalibleCommands(modelData) : 0
                    command: helper ? helper.command(modelData) : 0
                    onSetCommand: if (helper) helper.setCommand(modelData, command)
                    onRemove: if (helper) removeMissionItem(modelData)
                }
            }

            Button {
                id: addButton
                Layout.preferredWidth: palette.controlBaseSize * 11
                Layout.fillWidth: true
                text: qsTr("Add Item")
                iconSource: "qrc:/icons/add.svg"
                enabled: missionBox.currentIndex > -1
                onClicked: {
                    addMissionItem();
                    repeater.itemAt(repeater.count - 1).pick();
                }
            }
        }
    }
}
