import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property alias missionNames: missionBox.model
    property var missionItems

    signal missionSelected(string name)
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
                onCurrentTextChanged: missionSelected(currentText)
            }

            Button {
                iconSource: "qrc:/icons/add.svg"
            }

            Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
            }

            ComboBox {
                id: vehiclesBox
                Layout.fillWidth: true
                onCurrentTextChanged: missionSelected(currentText)
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
                    model: missionItems

                    MissionItemView {
                        anchors.left: parent.left
                        anchors.right: parent.right
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
            onClicked: addMissionItem()
        }
    }

    Frame {
        id: separator
        anchors.left: parent.left
        anchors.right: parent.right
        y: parent.height * 2 / 3
        height: 7
    }

    MouseArea {
        anchors.fill: separator
        drag.target: separator
        drag.axis: Drag.YAxis
        drag.minimumY: 0
        drag.maximumY: parent.height
    }
}
