import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "../Map"

Pane {
    id: root

    property alias missions: missionsBox.model
    property string selectedMission
    property int progress: progressBar.value

    signal selectMission(string name)
    signal addMission()
    signal removeMission()
    signal uploadMission()
    signal downloadMission()

    padding: 0
    onSelectedMissionChanged: {
        missionsBox.currentIndex = missionsBox.model.indexOf(selectedMission)
    }

    ColumnLayout {
        id: column
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        GridLayout {
            columns: 4
            Layout.margins: palette.margins

            Label {
                text: qsTr("Mission")
            }

            ComboBox {
                id: missionsBox
            }

            Button {
                iconSource: "qrc:/icons/add.svg"
                onClicked: addMission()
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                onClicked: removeMission()
            }

            Label {
                text: qsTr("Vehicle")
            }

            ComboBox {
                id: vehiclesBox
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
                onClicked: downloadMission()
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
                onClicked: uploadMission()
            }

            ProgressBar {
                id: progressBar
                to: 100
                Layout.columnSpan: 4
                Layout.fillWidth: true
            }
        }

        Item { // TODO: MissionItemView
            Layout.fillHeight: true
        }
    }

    MapView {
        id: map
        objectName: "map"
        anchors.left: column.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
