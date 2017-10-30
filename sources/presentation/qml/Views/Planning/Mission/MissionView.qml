import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../../Common"

ColumnLayout {
    id: root

    property alias missions: missionsBox.model
    property alias vehicles: vehiclesBox.model
    property alias selectedMission: missionsBox.currentIndex
    property alias assignedVehicle: vehiclesBox.currentIndex
    property int status: MissionAssignment.NotActual

    property bool missionVisible: false

    signal selectMission(int index)
    signal addMission()
    signal addItem(int command)
    signal removeMission()
    signal renameMission(string name)
    signal assignVehicle(int index)
    signal setMissionVisible(bool visible)
    signal uploadMission()
    signal downloadMission()
    signal cancelSyncMission()

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
            Layout.fillWidth: true
        }

        Controls.Button {
            id: edit
            toolTip: checked ? qsTr("Edit mission name") : qsTr("Cancel edit mission name")
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
            toolTip: qsTr("Add mission")
            iconSource: "qrc:/icons/add.svg"
            onClicked: addMission()
        }

        Controls.DelayButton {
            toolTip: qsTr("Remove mission")
            iconSource: "qrc:/icons/remove.svg"
            iconColor: palette.dangerColor
            enabled: selectedMission > 0 && assignedVehicle === 0
            onActivated: removeMission()
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
            toolTip: missionVisible ? qsTr("Hide mission") : qsTr("Show mission")
            iconSource: missionVisible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
            enabled: selectedMission > 0
            onClicked: setMissionVisible(!missionVisible)
        }

        Controls.Button {
            toolTip: qsTr("Download mission from MAV")
            iconSource: "qrc:/icons/download.svg"
            enabled: selectedMission > 0 && assignedVehicle > 0
            highlighted: status === MissionAssignment.Downloading
            onClicked: highlighted ? cancelSyncMission() : downloadMission()
        }

        Controls.Button {
            toolTip: qsTr("Upload mission to MAV")
            iconSource: "qrc:/icons/upload.svg"
            enabled: selectedMission > 0 && assignedVehicle > 0
            highlighted: status === MissionAssignment.Uploading
            onClicked: highlighted ? cancelSyncMission() : uploadMission()
        }
    }

    RowLayout {
        Controls.Button {
            toolTip: qsTr("Left")
            iconSource: "qrc:/icons/left.svg"
            enabled: itemsStatus.selectedItem > 0
            onClicked: itemsStatus.selectItem(itemsStatus.selectedItem - 1)
            onPressAndHold: itemsStatus.selectItem(0)
        }

        MissionItemsStatusView {
            id: itemsStatus
            objectName: "itemsStatus"
            Layout.fillWidth: true
        }

        Controls.Button {
            toolTip: qsTr("Right")
            iconSource: "qrc:/icons/right.svg"
            visible: itemsStatus.selectedItem < itemsStatus.count - 1
            onClicked: itemsStatus.selectItem(itemsStatus.selectedItem + 1)
            onPressAndHold: itemsStatus.selectItem(itemsStatus.count - 1)
        }

        Controls.Button {
            toolTip: qsTr("Add mission item")
            iconSource: "qrc:/icons/add.svg"
            visible: itemsStatus.selectedItem == itemsStatus.count - 1
            enabled: selectedMission > 0
            onClicked: if (!addMenu.visible) addMenu.open()

            Controls.Menu {
                id: addMenu
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Home")
                    iconSource: "qrc:/icons/home.svg"
                    enabled: itemsStatus.selectedItem == -1
                    onTriggered: addItem(MissionItem.Home)
                }

                Controls.MenuItem {
                    text: qsTr("Waypoint")
                    iconSource: "qrc:/icons/map-marker.svg"
                    enabled: itemsStatus.selectedItem >= 0
                    onTriggered: addItem(MissionItem.Waypoint)
                }

                Controls.MenuItem {
                    text: qsTr("Takeoff")
                    iconSource: "qrc:/icons/takeoff.svg"
                    enabled: itemsStatus.selectedItem >= 0
                    onTriggered: addItem(MissionItem.Takeoff)
                }

                Controls.MenuItem {
                    text: qsTr("Landing")
                    iconSource: "qrc:/icons/landing.svg"
                    enabled: itemsStatus.selectedItem >= 0
                    onTriggered: addItem(MissionItem.Landing)
                }
            }
        }
    }

    MissionItemEditView {
        id: itemEdit
        objectName: "itemEdit"
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
