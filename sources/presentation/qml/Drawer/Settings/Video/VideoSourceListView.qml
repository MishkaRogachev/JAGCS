import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: videoSourceList

    property var videoDevices
    property int activeVideo: 0

    property alias videos: list.model

//    onVisibleChanged: drawer.filterEnabled = visible
//    Component.onCompleted: drawer.filterEnabled = true
    onActiveVideoChanged: {
        presenter.saveActiveVideo(activeVideo);
        video.updateActiveVideo();
    }

    implicitWidth: industrial.baseSize * 10

//    Connections{
//        target: drawer
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
        anchors.margins: industrial.shadowSize
        anchors.topMargin: spacing + industrial.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: industrial.spacing
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
            anchors.margins: industrial.margins
            text: qsTr("No video")
            Controls.ButtonGroup.group: radioGroup
            checked: activeVideo == 0
            onClicked: activeVideo = 0
        }
    }

    Controls.FloatButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: parent.width / 3
        anchors.bottom: parent.bottom
        highlighted: true
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Add video source")
        onClicked: if (!addMenu.visible) addMenu.open()
    }

    Controls.Menu {
        id: addMenu
        y: addButton.y - height
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
