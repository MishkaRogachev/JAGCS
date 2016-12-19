import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    property alias missionNames: missionBox.model
    property var vehicleNames: []
    property var missionItems: []

    signal missionSelected(string name)
    signal addMission()
    signal removeMission()

    signal addMissionItem()
    signal removeMissionItem(QtObject item)

    signal downloadMission(string name)
    signal uploadMission(string name)

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
                onModelChanged: {
                    currentIndex = -1;
                    currentIndex = count - 1;
                }
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

            ProgressBar {
                Layout.fillWidth: true
                anchors.verticalCenter: parent.verticalCenter
            }

            MenuButton {
                iconSource: "qrc:/icons/download.svg"
                model: vehicleNames
                onTriggered: downloadMission(data)
            }

            MenuButton {
                iconSource: "qrc:/icons/upload.svg"
                model: vehicleNames
                onTriggered: uploadMission(data)
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
                        // FIXME: annoying binding loops warnings
                        anchors.left: parent.left
                        anchors.right: parent.right
                        seq: modelData.sequence
                        command: modelData.command
                        onCommandChanged: modelData.setCommand(command)
                        latitude: modelData.latitude
                        onLatitudeChanged: modelData.setLatitude(latitude)
                        longitude: modelData.longitude
                        onLongitudeChanged: modelData.setLongitude(longitude)
                        altitude: modelData.altitude
                        onAltitudeChanged: modelData.setAltitude(altitude)
                        relativeAltitude: modelData.relativeAltitude
                        onRelativeAltitudeChanged: modelData.setRelativeAltitude(relativeAltitude)
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
