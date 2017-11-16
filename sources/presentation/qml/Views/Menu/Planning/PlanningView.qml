import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Item {
    id: root

    property var missions

    signal addMission()

    implicitWidth: palette.controlBaseSize * 11

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: addRow.height
        contentHeight: column.height
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            visible: missionRepeater.count == 0
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

            Repeater {
                id: missionRepeater
                model: vehicles

//                MissionView {
//                    id: descriptionView
//                    Layout.fillWidth: true
//                    Component.onCompleted: modelData.setView(descriptionView)
//                }
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
            onClicked: addMission()
            Layout.fillWidth: true
        }

        // TODO: add Area, add Survey
    }
}
