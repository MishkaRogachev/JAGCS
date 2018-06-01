import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: videoSourceList

    property var videoDevices: []
    property int activeVideo: 0

    property alias videos: list.model

//    onVisibleChanged: menu.filterEnabled = visible
//    Component.onCompleted: menu.filterEnabled = true
    onActiveVideoChanged: presenter.saveActiveVideo(activeVideo)

    implicitWidth: sizings.controlBaseSize * 10

//    Connections{
//        target: menu
//        onFilter: presenter.filter(text)
//    }

    VideoSourceListPresenter {
        id: presenter
        view: videoSourceList
    }

    Controls.ButtonGroup { id: radioGroup }

    ListView {
        id: list
        anchors.fill: parent
        anchors.margins: sizings.shadowSize
        anchors.topMargin: spacing + sizings.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: VideoSourceView {
            width: parent.width
            videoId: model.videoId
            selected: activeVideo == videoId
            onSetActiveVideo: activeVideo = videoId
        }
    }

    Controls.Label {
        anchors.centerIn: parent
        text: qsTr("No video present")
        visible: list.count === 0
    }

    Controls.BottomBar {
        width: parent.width
        anchors.bottom: parent.bottom

        Controls.RadioButton {
            anchors.left: parent.left
            anchors.margins: sizings.margins
            text: qsTr("No video")
            Controls.ButtonGroup.group: radioGroup
            checked: activeVideo == 0
            onClicked: activeVideo = 0
        }
    }

    Controls.RoundButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: parent.width / 3
        anchors.bottom: parent.bottom
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Add video source")
        onClicked: if (!addMenu.visible) addMenu.open()

        Controls.Menu {
            id: addMenu
            x: (parent.width - width) / 2
            y: parent.height - height
            width: list.width

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
