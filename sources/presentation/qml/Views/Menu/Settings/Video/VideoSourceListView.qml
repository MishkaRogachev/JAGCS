import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: videoSourceList

    property var videoSourceIds: []
    property var videoDevices: []
    property int activeVideo: -1

    implicitWidth: sizings.controlBaseSize * 11

    onActiveVideoChanged: video.setActiveVideo(activeVideo)

    VideoSourceListPresenter {
        id: presenter
        view: videoSourceList
        Component.onCompleted: {
            updateCameraInfo();
            updateVideoSources();
        }
        Component.onDestruction: saveActiveVideo(activeVideo)
    }

    Controls.ButtonGroup { id: radioGroup }

    ColumnLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Frame {
            Layout.fillWidth: true
            Layout.rightMargin: sizings.shadowSize

            RowLayout {
                id: grid
                anchors.fill: parent
                spacing: sizings.spacing

                Controls.RadioButton {
                    checked: activeVideo == -1
                    text: qsTr("No video")
                    horizontalAlignment: Text.AlignHCenter
                    Controls.ButtonGroup.group: radioGroup
                    onClicked: activeVideo = -1
                    Layout.fillWidth: true
                }
            }
        }

        ListView {
            spacing: sizings.spacing
            model: videoSourceIds
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            Controls.ScrollBar.vertical: Controls.ScrollBar {}

            delegate: VideoSourceView {
                width: parent.width - sizings.shadowSize
                videoId: modelData
                selected: activeVideo == videoId
                onSetActiveVideo: activeVideo = videoId
            }

            Controls.Frame {
                visible: parent.count === 0
                width: parent.width - sizings.shadowSize
                height: label.height + sizings.margins * 2

                Controls.Label {
                    id: label
                    text: qsTr("No video sources present")
                    width: parent.width
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        Controls.Button {
            id: addButton
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            text: qsTr("Add video source")
            iconSource: "qrc:/icons/add.svg"
            onClicked: if (!addMenu.visible) addMenu.open()

            Controls.Menu {
                id: addMenu
                implicitWidth: parent.width
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Device")
                    implicitWidth: parent.width
                    onTriggered: presenter.addDeviceVideo()
                }

                Controls.MenuItem {
                    text: qsTr("Stream")
                    implicitWidth: parent.width
                    onTriggered: presenter.addStreamVideo()
                }
            }
        }
    }
}
