import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: missionEdit

    property int missionId: 0

    property int sequence: -1
    property int count: 0

    property string name
    property alias selectedItemId: itemList.selectedItemId

    onMissionIdChanged: {
        presenter.setMission(missionId);
        if (missionId) presenter.selectItem(0);
    }
    onNameChanged: {
        if (missionId > 0)
        {
            if (name.length > 0) menu.submode = name;
            else menu.submode = qsTr("Mission");
        }
        else menu.submode = "";
    }
    onSelectedItemIdChanged: {
        presenter.setItem(selectedItemId);
        if (map) map.selectedItemId = selectedItemId;
    }
    Component.onDestruction: {
        menu.submode = "";
        if (map) map.selectedItemId = 0;
    }

    spacing: sizings.spacing

    MissionEditPresenter {
        id: presenter
        view: missionEdit
    }

    RowLayout {
        spacing: sizings.spacing

        MissionAssignmentView {
            id: assignment
            missionId: missionEdit.missionId
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: highlighted ? qsTr("Cancel sync") : qsTr("Download mission")
            iconSource: "qrc:/icons/download.svg"
            highlighted: assignment.status === MissionAssignment.Downloading
            enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline
            onClicked: highlighted ? assignment.cancelSync() : assignment.download()
        }

        Controls.Button {
            tipText: highlighted ? qsTr("Cancel sync") : qsTr("Upload mission")
            iconSource: "qrc:/icons/upload.svg"
            highlighted: assignment.status === MissionAssignment.Uploading
            enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline
            onClicked: highlighted ? assignment.cancelSync() : assignment.upload()
        }
    }

    Flickable {
        id: flickable
        contentWidth: itemList.width
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        onMovementStarted: drawer.interactive = false
        onMovementEnded: drawer.interactive = true
        Layout.minimumHeight: sizings.controlBaseSize
        Layout.fillWidth: true

        MissionItemListView {
            id: itemList
            height: parent.height
            missionId: missionEdit.missionId
            onSelectionRequest: missionEdit.selectedItemId = itemId
            onCheckItemX: {
                var dX = x - flickable.contentX;
                if (dX < 0) {
                    flickable.contentX = x;
                }
                else if (dX > flickable.width - sizings.controlBaseSize) {
                    flickable.contentX = x - flickable.width + sizings.controlBaseSize;
                }
            }
        }
    }

    RowLayout {
        spacing: sizings.spacing

        Controls.Button {
            tipText: qsTr("Left")
            iconSource: "qrc:/icons/left.svg"
            enabled: sequence > 0
            onClicked: presenter.selectItem(sequence - 1)
            onPressAndHold: presenter.selectItem(0)
        }

        Controls.Label {
            text: sequence >= 0 ? ((sequence + 1) + "/" + count) : "-"
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Right")
            iconSource: "qrc:/icons/right.svg"
            enabled: sequence + 1 < count
            onClicked: presenter.selectItem(sequence + 1)
            onPressAndHold: presenter.selectItem(count - 1)
        }

        Controls.Button {
            tipText: qsTr("Add mission item")
            iconSource: "qrc:/ui/plus.svg"
            enabled: missionId > 0
            onClicked: if (!addMenu.visible) addMenu.open()

            Controls.Menu {
                id: addMenu
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Home")
                    iconSource: "qrc:/icons/home.svg"
                    enabled: sequence == -1
                    onTriggered: presenter.addItem(MissionItem.Home, map.centerOffsetted)
                }

                Controls.MenuItem {
                    text: qsTr("Waypoint")
                    iconSource: "qrc:/icons/map-marker.svg"
                    enabled: sequence >= 0
                    onTriggered: presenter.addItem(MissionItem.Waypoint, itemEdit.position)
                }

                Controls.MenuItem {
                    text: qsTr("Takeoff")
                    iconSource: "qrc:/icons/takeoff.svg"
                    enabled: sequence >= 0
                    onTriggered: presenter.addItem(MissionItem.Takeoff, itemEdit.position)
                }

                Controls.MenuItem {
                    text: qsTr("Landing")
                    iconSource: "qrc:/icons/landing.svg"
                    enabled: sequence >= 0
                    onTriggered: presenter.addItem(MissionItem.Landing, itemEdit.position)
                }
            }
        }

        Controls.Button {
            tipText: qsTr("More")
            iconSource: "qrc:/ui/dots.svg"
            enabled: sequence > -1
            onClicked: if (!dangerMenu.visible) dangerMenu.open()

            Controls.Menu {
                id: dangerMenu
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Move right")
                    iconSource: "qrc:/icons/right_right.svg"
                    enabled: sequence > 0 && sequence + 1 < count
                    onTriggered: presenter.changeSequence(sequence + 1)
                }

                Controls.MenuItem {
                    text: qsTr("Move left")
                    iconSource: "qrc:/icons/left_left.svg"
                    enabled: sequence > 1
                    onTriggered: presenter.changeSequence(sequence - 1)
                }

                Controls.MenuItem {
                    text: qsTr("Remove")
                    iconSource: "qrc:/icons/remove.svg"
                    iconColor: customPalette.dangerColor
                    onTriggered: presenter.removeItem()
                }
            }
        }
    }

    MissionItemEditView {
        id: itemEdit
        itemId: missionEdit.selectedItemId
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
