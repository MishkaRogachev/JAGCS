import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property QtObject helper

    property alias missionNames: missionBox.model
    property var vehicleNames: []

    property int currentCount: 0
    property int totalCount: 0

    property var missionItems: []

    signal missionSelected(string name)
    signal addMission()
    signal removeMission()

    signal addMissionItem()
    signal removeMissionItem(QtObject item)

    signal downloadMission(string name)
    signal uploadMission(string name)

    MissionMapView {
        id: map
        objectName: "map"
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: pane.right
        anchors.right: parent.right
    }

    Pane {
        id: pane
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        ColumnLayout {
            height: parent.height

            RowLayout {
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

                MenuButton {
                    iconSource: "qrc:/icons/download.svg"
                    model: vehicleNames
                    enabled: missionBox.currentIndex != -1
                    onTriggered: downloadMission(data)
                }

                MenuButton {
                    iconSource: "qrc:/icons/upload.svg"
                    model: vehicleNames
                    enabled: missionBox.currentIndex != -1
                    onTriggered: uploadMission(data)
                }
            }

            ProgressBar {
                Layout.fillWidth: true
                from: 0
                to: totalCount
                value: currentCount
            }

            Flickable {
                id: flickable
                Layout.preferredWidth: contentWidth
                Layout.fillHeight: true
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
                            if (column.height > flickable.height)
                                flickable.contentY = column.height - flickable.height;
                        }

                        MissionItemView {
                            item: modelData
                            avalibleCommands: helper.avalibleCommands(modelData)
                            command: helper.command(modelData)
                            onSetCommand: helper.setCommand(modelData, command)
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
                onClicked: {
                    addMissionItem();
                    repeater.itemAt(repeater.count - 1).pick();
                }
            }
        }
    }
}
