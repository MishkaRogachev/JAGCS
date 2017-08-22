import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property alias missions: missionsBox.model
    property alias vehicles: vehiclesBox.model
    property alias selectedMission: missionsBox.currentIndex
    property alias assignedVehicle: vehiclesBox.currentIndex
    property int status: MissionAssignment.NotActual
    property var statuses: []

    property bool missionVisible: false

    signal selectMission(int index)
    signal addMission()
    signal addItem()
    signal removeMission()
    signal renameMission(string name)
    signal assignVehicle(int index)
    signal setMissionVisible(bool visible)
    signal uploadMission()
    signal downloadMission()

    Layout.margins: palette.margins
    spacing: palette.spacing
    width: palette.controlBaseSize * 11

    GridLayout {
        columns: 5

        Controls.Label {
            text: qsTr("Mission")
        }

        Controls.ComboBox {
            id: missionsBox
            visible: !edit.checked
            onCurrentIndexChanged: selectMission(currentIndex);
            Layout.fillWidth: true
        }

        Controls.TextField {
            id: nameEdit
            visible: edit.checked
        }

        Controls.Button {
            id: edit
            iconSource: "qrc:/icons/edit.svg"
            checkable: true
            enabled: selectedMission > 0
            onCheckedChanged: {
                if (checked)
                {
                    nameEdit.text = missionsBox.currentText;
                    nameEdit.forceActiveFocus();
                    nameEdit.selectAll();
                }
                else
                {
                    renameMission(nameEdit.text);
                }
            }
        }

        Controls.Button {
            iconSource: "qrc:/icons/add.svg"
            onClicked: addMission()
        }

        Controls.Button {
            iconSource: "qrc:/icons/remove.svg"
            iconColor: palette.negativeColor
            enabled: selectedMission > 0 && assignedVehicle == 0
            onClicked: removeMission()
        }

        Controls.Label {
            text: qsTr("Vehicle")
        }

        Controls.ComboBox {
            id: vehiclesBox
            enabled: selectedMission > 0
            onCurrentIndexChanged: assignVehicle(currentIndex)
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
            enabled: selectedMission > 0
            onClicked: setMissionVisible(!missionVisible)
        }

        Controls.Button {
            iconSource: "qrc:/icons/download.svg"
            enabled: selectedMission > 0 && assignedVehicle > 0
            checked: status === MissionAssignment.Downloading
            onClicked: downloadMission() // TODO: cancel download process
        }

        Controls.Button {
            iconSource: "qrc:/icons/upload.svg"
            enabled: selectedMission > 0 && assignedVehicle > 0
            checked: status === MissionAssignment.Uploading
            onClicked: uploadMission() // TODO: cancel upload process
        }
    }

    RowLayout {

        Flickable {
            id: flickable
            Layout.fillWidth: true
            implicitHeight: row.height
            contentWidth: row.width
            boundsBehavior: Flickable.StopAtBounds
            clip: true

            RowLayout {
                id: row
                spacing: 1

                Repeater {
                    id: repeater
                    model: statuses

                    Item {
                        Layout.minimumWidth: palette.controlBaseSize
                        Layout.minimumHeight: palette.controlBaseSize

                        property bool selected: missionItem.sequence == index
                        onSelectedChanged: {
                            if (!selected) return;

                            if (x + width > flickable.width + flickable.contentX) {
                                flickable.contentX = x + width - flickable.width;
                            }
                            else if (x < flickable.contentX) {
                                flickable.contentX = x;
                            }
                        }

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.height
                            height: width
                            radius: width / 2
                            color: selected ? palette.selectionColor : palette.raisedColor
                            border.color: {
                                switch (parseInt(modelData)) {
                                case MissionItem.Actual: return palette.positiveColor;
                                case MissionItem.StatusNone: return palette.sunkenColor;
                                case MissionItem.Downloading:
                                case MissionItem.Uploading: return palette.neutralColor;
                                case MissionItem.NotActual:
                                default: return palette.negativeColor;
                                }
                            }
                            border.width: 4

                            Controls.Label { // TODO: mode icon
                                text: index
                                color: selected ? palette.selectedTextColor : palette.textColor
                                anchors.centerIn: parent
                                font.bold: true
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: missionItem.selectItem(index)
                            }
                        }
                    }
                }
            }
        }
    }

    MissionItemView {
        id: missionItem
        objectName: "missionItem"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
