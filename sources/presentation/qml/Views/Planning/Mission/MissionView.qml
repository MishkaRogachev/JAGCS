import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"

ColumnLayout {
    id: root

    property alias missions: missionsBox.model
    property alias vehicles: vehiclesBox.model
    property alias selectedMission: missionsBox.currentIndex
    property alias assignedVehicle: vehiclesBox.currentIndex
    property var statuses: []

    signal selectMission(int index)
    signal addMission()
    signal addItem()
    signal removeMission()
    signal renameMission(string name)
    signal assignVehicle(int index)
    signal uploadMission()
    signal downloadMission()

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
            //checked: assignedStatus == MissionAssignment.Downloading
            onClicked: downloadMission()
        }

        Button {
            iconSource: "qrc:/icons/upload.svg"
            enabled: selectedMission > 0 && assignedVehicle > 0
            //checked: assignedStatus == MissionAssignment.Uploading
            onClicked: uploadMission()
        }
    }

    RowLayout {

        Button {
            iconSource: "qrc:/icons/home.svg"
            onClicked: flickable.contentX = 0// TODO: go home
        }

        Button {
            iconSource: "qrc:/icons/left.svg"
            autoRepeat: true
            onClicked: flickable.flick(palette.controlBaseSize * 10, 0)
            enabled: row.width > flickable.width && flickable.contentX > 0
        }

        Button {
            iconSource: "qrc:/icons/right.svg"
            autoRepeat: true
            onClicked: flickable.flick(-palette.controlBaseSize * 10, 0)
            enabled: row.width > flickable.width &&
                     flickable.contentX < (row.width - flickable.width)
        }

        Flickable {
            id: flickable
            Layout.fillWidth: true
            implicitHeight: row.height
            contentWidth: row.width
            clip: true

            RowLayout {
                id: row
                spacing: 1

                Repeater {
                    id: repeater
                    model: statuses
                    onModelChanged: {
                        if (row.width > flickable.width)
                            flickable.contentX = row.width - flickable.width;
                    }

                    Item {
                        Layout.minimumWidth: palette.controlBaseSize
                        Layout.minimumHeight: palette.controlBaseSize

                        property bool selected: missionItem.sequence === (index + 1)

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
        }

        Button {
            iconSource: "qrc:/icons/add.svg"
            enabled: selectedMission > 0
            onClicked: addItem()
        }
    }

    MissionItemView {
        id: missionItem
        objectName: "missionItem"
    }
}
