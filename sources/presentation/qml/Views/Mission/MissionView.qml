import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property alias missionNames: missionBox.model
    property alias vehicleNames: vehiclesBox.model
    property var missionItems

    signal missionSelected(string name)
    signal vehicleSelected(string name)
    signal addMission()
    signal removeMission()
    signal addMissionItem()
    signal removeMissionItem(QtObject item)

    MissionMapView {
        id: map
        objectName: "map"
        anchors.fill: parent
    }

    Pane {
        anchors.fill: missionsColumn
    }

    ColumnLayout {
        id: missionsColumn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: separator.bottom
        anchors.bottom: parent.bottom

        RowLayout {
            ComboBox {
                id: missionBox
                Layout.fillWidth: true
                onModelChanged: currentIndex = count - 1;
                onCurrentTextChanged: missionSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/add.svg"
                onClicked: addMission()
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
                onClicked: removeMission()
            }

            ComboBox {
                id: vehiclesBox
                Layout.fillWidth: true
                onCurrentTextChanged: vehicleSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/download.svg"
            }

            Button {
                iconSource: "qrc:/icons/upload.svg"
            }
        }

        Flickable {
            id: flickable
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            contentWidth: column.width
            contentHeight: column.height

            ColumnLayout {
                id: column
                width: flickable.width
                spacing: 8

                Repeater {
                    id: repeater
                    model: missionItems
                    onModelChanged: {
                        if (column.height > flickable.height)
                            flickable.contentY = column.height - flickable.height;
                    }

                    MissionItemView {
                        anchors.left: parent.left
                        anchors.right: parent.right
                        seq: modelData.sequence
                        coordinate: modelData.coordinate
                        onCoordinateChanged: modelData.setCoordinate(coordinate)
                        onRemove: removeMissionItem(modelData)
                    }
                }
            }
        }

        Button {
            id: addButton
            Layout.fillWidth: true
            text: qsTr("Add Item")
            iconSource: "qrc:/icons/add.svg"
            enabled: missionBox.currentIndex > -1
            onClicked: {
                addMissionItem();
                repeater.itemAt(repeater.count - 1).pick();
            }
        }
    }

    Frame { // TODO: separator control
        id: separator
        anchors.left: parent.left
        anchors.right: parent.right
        y: parent.height * 2 / 3
        height: 7
    }

    MouseArea {
        anchors.fill: separator
        anchors.margins: -8
        drag.target: separator
        drag.axis: Drag.YAxis
        drag.minimumY: 0
        drag.maximumY: parent.height
        cursorShape: Qt.SizeVerCursor
    }
}
