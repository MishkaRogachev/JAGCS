import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import "qrc:/Views/Common"

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
            if (name.length > 0) drawer.submode = name;
            else drawer.submode = qsTr("Mission");
        }
        else drawer.submode = "";
    }
    onSelectedItemIdChanged: {
        presenter.setItem(selectedItemId);
        if (map) map.selectedItemId = selectedItemId;
    }
    Component.onDestruction: {
        drawer.submode = "";
        if (map) map.selectedItemId = 0;
    }

    spacing: industrial.spacing

    MissionEditPresenter {
        id: presenter
        view: missionEdit
    }

    RowLayout {
        spacing: 0

        MissionAssignmentView {
            id: assignment
            missionId: missionEdit.missionId
            Layout.fillWidth: true
        }

        SaveRestore {
            enabled: itemEdit.changed && itemEdit.editEnabled
            onSave: itemEdit.save()
            onRestore: itemEdit.update()
        }

        Controls.Button {
            tipText: qsTr("More")
            iconSource: "qrc:/ui/dots.svg"
            flat: true
            enabled: sequence > -1
            onClicked: moreMenu.visible ? moreMenu.close() : moreMenu.open()

            Controls.Menu {
                id: moreMenu
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Center on map")
                    iconSource: "qrc:/icons/center.svg"
                    enabled: map.trackingVehicleId === 0 && itemEdit.position.isValid && map.visible
                    onTriggered: map.setCenterOffsetted(itemEdit.position);
                }

                Controls.MenuItem {
                    text: qsTr("Put in center")
                    iconSource: "qrc:/icons/put_center.svg"
                    enabled: map.trackingVehicleId === 0 && map.visible
                    onTriggered: {
                        itemEdit.position = map.centerOffsetted;
                        itemEdit.save();
                    }
                }

                Controls.MenuItem {
                    property bool downloading: assignment.status === MissionAssignment.Downloading
                    text: downloading ? qsTr("Cancel sync") : qsTr("Download mission")
                    iconSource: "qrc:/icons/download.svg"
                    highlighted: downloading
                    enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline
                    onTriggered: downloading ? assignment.cancelSync() : assignment.download()
                }

                Controls.MenuItem {
                    property bool uploading: assignment.status === MissionAssignment.Uploading
                    text: uploading ? qsTr("Cancel sync") : qsTr("Upload mission")
                    iconSource: "qrc:/icons/upload.svg"
                    highlighted: uploading
                    enabled: assignment.assignedVehicleId > 0 && assignment.vehicleOnline
                    onTriggered: uploading ? assignment.cancelSync() : assignment.upload()
                }

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
                    iconColor: industrial.colors.negative
                    onTriggered: presenter.removeItem()
                }
            }
        }
    }

    RowLayout {
        spacing: 0

        Controls.Button {
            tipText: qsTr("Left")
            iconSource: "qrc:/icons/left.svg"
            flat: true
            enabled: sequence > 0
            onClicked: presenter.selectItem(sequence - 1)
            onPressAndHold: presenter.selectItem(0)
        }

        Flickable {
            id: flickable
            contentWidth: itemList.width
            clip: true
            boundsBehavior: Flickable.StopAtBounds
            onMovementStarted: drawer.interactive = false
            onMovementEnded: drawer.interactive = true
            Layout.minimumHeight: industrial.baseSize
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
                    else if (dX > flickable.width - industrial.baseSize) {
                        flickable.contentX = x - flickable.width + industrial.baseSize;
                    }
                }
            }
        }

        Controls.Button {
            tipText: qsTr("Right")
            iconSource: "qrc:/icons/right.svg"
            flat: true
            enabled: sequence + 1 < count
            onClicked: presenter.selectItem(sequence + 1)
            onPressAndHold: presenter.selectItem(count - 1)
        }

        Controls.Button {
            tipText: qsTr("Add mission item")
            iconSource: "qrc:/ui/plus.svg"
            flat: true
            enabled: missionId > 0
            onClicked: addMenu.visible ? addMenu.close() : addMenu.open()

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
    }

    MissionItemEditView {
        id: itemEdit
        itemId: missionEdit.selectedItemId
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
