import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: missionEdit

    property int missionId: 0

    property int sequence: -1
    property int count: 0

    property alias name: nameLabel.text
    property alias selectedItemId: itemList.selectedItemId
    property alias picking: itemEdit.picking

    implicitWidth: sizings.controlBaseSize * 11
    spacing: sizings.spacing

    onMissionIdChanged: {
        presenter.setMission(missionId);
        presenter.selectItem(0);
    }
    onSelectedItemIdChanged: {
        presenter.setItem(selectedItemId);
        if (map) map.selectedItemId = selectedItemId;
    }

    Component.onDestruction: if (map) map.selectedItemId = 0

    Connections {
        target: map
        ignoreUnknownSignals: true

        onSelectItem: {
            if (missionEdit.missionId !== missionId) return;
            selectedItemId = itemId;
        }
    }

    MissionEditPresenter {
        id: presenter
        view: missionEdit
    }

    RowLayout {
        spacing: sizings.spacing

        Controls.Button {
            tipText: qsTr("Back to planning list")
            iconSource: "qrc:/icons/left.svg"
            flat: true
            onClicked: selectedMissionId = 0
        }

        Controls.Label {
            id: nameLabel
            text: qsTr("Unknown mission")
        }
    }

    Flickable {
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
        }
    }

    RowLayout {
        spacing: sizings.spacing

        Controls.Label {
            text: qsTr("Item")
            Layout.fillWidth: true
        }

        Controls.DelayButton {
            tipText: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            iconColor: customPalette.dangerColor
            enabled: sequence > -1
            onActivated: presenter.removeItem()
        }

        Controls.Button {
            tipText: qsTr("Move left")
            iconSource: "qrc:/icons/left_left.svg"
            enabled: sequence > 1
            onClicked: presenter.changeSequence(sequence - 1)
        }

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
            tipText: qsTr("Move right")
            iconSource: "qrc:/icons/right_right.svg"
            enabled: sequence > 0 && sequence + 1 < count
            onClicked: presenter.changeSequence(sequence + 1)
        }

        Controls.Button {
            tipText: qsTr("Add mission item")
            iconSource: "qrc:/icons/add.svg"
            enabled: missionId > 0
            onClicked: if (!addMenu.visible) addMenu.open()

            Controls.Menu {
                id: addMenu
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Home")
                    iconSource: "qrc:/icons/home.svg"
                    enabled: sequence == -1
                    onTriggered: presenter.addItem(MissionItem.Home)
                }

                Controls.MenuItem {
                    text: qsTr("Waypoint")
                    iconSource: "qrc:/icons/map-marker.svg"
                    enabled: sequence >= 0
                    onTriggered: presenter.addItem(MissionItem.Waypoint)
                }

                Controls.MenuItem {
                    text: qsTr("Takeoff")
                    iconSource: "qrc:/icons/takeoff.svg"
                    enabled: sequence >= 0
                    onTriggered: presenter.addItem(MissionItem.Takeoff)
                }

                Controls.MenuItem {
                    text: qsTr("Landing")
                    iconSource: "qrc:/icons/landing.svg"
                    enabled: sequence >= 0
                    onTriggered: presenter.addItem(MissionItem.Landing)
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
