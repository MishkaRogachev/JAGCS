import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../Map"

Pane {
    id: root

    property QtObject helper

    property QtObject selectedVehicle

    property alias missionNames: missionBox.model
    property alias vehicleNames: vehicleBox.model

    property alias selectedMission: missionBox.currentIndex
    property alias selectedVehicleId: vehicleBox.currentIndex

    property int currentProgress: 0
    property int totalProgress: 0
    property string statusString: qsTr("None")

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

    MapView {
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
        anchors.leftMargin: palette.margins
        anchors.rightMargin: palette.margins
        height: palette.controlBaseSize + palette.spacing

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
                enabled: selectedMission != -1
                onModelChanged: {
                    currentIndex = -1;
                    currentIndex = count - 1;
                }
                onCurrentTextChanged: vehicleSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
                enabled: selectedMission != -1 && selectedVehicleId > 0
                onClicked: downloadMission()
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
                enabled: selectedMission != -1 && selectedVehicleId > 0
                onClicked: uploadMission()
            }

            ProgressBar {
                Layout.fillWidth: true
                from: 0
                to: totalProgress
                value: currentProgress
            }

            Label {
                text: statusString
                horizontalAlignment: Qt.AlignHCenter
                Layout.preferredWidth: palette.controlBaseWidth
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

                MissionItemView { // TODO: separate mission item edit
                    item: modelData
                    Layout.preferredWidth: column.width
                    avalibleCommands: helper ? helper.avaliableCommands(modelData) : 0
                    command: helper ? helper.command(modelData) : 0
                    onSetCommand: if (helper) helper.setCommand(modelData, command)
                    onRemove: removeMissionItem(modelData)
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
