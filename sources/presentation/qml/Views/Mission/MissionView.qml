import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"
import "../Map"

Pane {
    id: root

    property alias missions: missionsBox.model
    property alias vehicles: vehiclesBox.model
    property alias selectedMission: missionsBox.currentIndex
    property alias assignedVehicle: vehiclesBox.currentIndex
    property int assignedStatus: MissionAssignment.Unknown
    property var statuses: []

    signal selectMission(int index)
    signal addMission()
    signal removeMission()
    signal renameMission(string name)
    signal assignVehicle(int index)
    signal uploadMission()
    signal downloadMission()

    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Layout.margins: palette.margins
        spacing: palette.spacing

        GridLayout {
            columns: 5

            Label {
                text: qsTr("Mission")
            }

            ComboBox {
                id: missionsBox
                visible: !edit.checked
                onCurrentIndexChanged: selectMission(currentIndex);
            }

            TextField {
                id: nameEdit
                visible: edit.checked
            }

            Button {
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

            Button {
                iconSource: "qrc:/icons/add.svg"
                onClicked: addMission()
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                enabled: selectedMission > 0
                onClicked: removeMission()
            }

            Label {
                text: qsTr("Vehicle")
            }

            ComboBox {
                id: vehiclesBox
                enabled: selectedMission > 0
                Layout.columnSpan: 2
                onCurrentIndexChanged: assignVehicle(currentIndex)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
                enabled: selectedMission > 0 && assignedVehicle > 0
                checked: assignedStatus == MissionAssignment.Downloading
                onClicked: downloadMission()
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
                enabled: selectedMission > 0 && assignedVehicle > 0
                checked: assignedStatus == MissionAssignment.Uploading
                onClicked: uploadMission()
            }
        }

        RowLayout {
            spacing: 0

            Label {
                visible: repeater.count == 0
                text: qsTr("Not synchronized")
                horizontalAlignment: Qt.AlignHCenter
                Layout.fillWidth: true
            }

            Repeater {
                id: repeater
                model: statuses

                Item {
                    Layout.fillWidth: true
                    Layout.minimumHeight: palette.controlBaseSize

                    property bool selected: missionItem.sequence === (index + 1)

                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.height
                        height: width
                        radius: width / 2
                        color: selected ? palette.selectionColor : palette.raisedColor
                        border.color: {
                            switch (modelData) {
                            case MissionAssignment.Actual: return palette.positiveColor;
                            case MissionAssignment.Downloading:
                            case MissionAssignment.Uploading: return palette.neutralColor;
                            case MissionAssignment.NotActual:
                            default: return palette.negativeColor;
                            }
                        }
                        border.width: 4

                        Label { // TODO: mode icon
                            text: index + 1
                            color: selected ? palette.selectedTextColor : palette.textColor
                            anchors.centerIn: parent
                            font.bold: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: missionItem.selectItem(index + 1)
                        }
                    }
                }
            }
        }

        MissionItemView {
            id: missionItem
            objectName: "missionItem"
        }
    }

    MapView {
        id: map
        objectName: "map"
        anchors.left: column.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: palette.margins
    }
}
