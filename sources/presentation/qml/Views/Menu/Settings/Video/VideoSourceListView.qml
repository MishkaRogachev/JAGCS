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
    onActiveVideoChanged: video.updateActiveVideo()

    VideoSourceListPresenter {
        id: presenter
        view: videoSourceList
        Component.onCompleted: {
            updateCameraInfo();
            updateVideoSources();
        }
    }

    Controls.ButtonGroup { id: radioGroup }

    ListView {
        anchors.fill: parent
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        model: videoSourceIds

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        delegate: VideoSourceView {
            width: parent.width
            videoId: modelData
            selected: activeVideo == videoId
            onSetActiveVideo: presenter.setActiveVideo(videoId)
        }

        Controls.Frame {
            visible: parent.count === 0
            width: parent.width
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
