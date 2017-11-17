import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

import "Mission"

Item {
    id: planning

    property var vehicles: []

    implicitWidth: palette.controlBaseSize * 10

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: addRow.height
        contentHeight: Math.max(column.height, frame.height)
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            id: frame
            visible: missions.model.count === 0
            width: parent.width
            height: label.height + palette.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No items present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            anchors.centerIn: parent
            spacing: palette.spacing

            MissionListView {
                id: missions
                objectName: "missions"
            }
        }
    }

    RowLayout {
        id: addRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: palette.spacing

        Controls.Button {
            text: qsTr("Add Mission")
            iconSource: "qrc:/icons/add.svg"
            onClicked: missions.addMission()
            Layout.fillWidth: true
        }

        // TODO: add Area, add Survey
    }
}
