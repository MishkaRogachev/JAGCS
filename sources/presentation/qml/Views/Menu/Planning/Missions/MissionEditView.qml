import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: missionEdit

    property int sequence: 0
    property int count: 0

    property alias missionId: itemList.missionId
    property alias selectedItemId: itemList.selectedItemId
    property alias picking: itemEdit.picking

    implicitWidth: sizings.controlBaseSize * 11
    spacing: sizings.spacing

    onSelectedItemIdChanged: presenter.setItem(selectedItemId)

    MissionEditPresenter {
        id: presenter
        view: missionEdit
        Component.onCompleted: setMission(missionId)
    }

    MissionItemListView {
        id: itemList
        missionId: missionEdit.missionId
        onSelectionRequest: missionEdit.selectedItemId = itemId
        Layout.fillWidth: true
    }

    RowLayout
    {
        Controls.Label {
            text: qsTr("Item")
            Layout.fillWidth: true
        }

        Controls.DelayButton {
            tipText: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            iconColor: palette.dangerColor
            enabled: sequence > -1
            onActivated: presenter.remove()
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

