import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Controls.Card {
    id: videoView

    property int videoId: 0
    property int type: VideoSource.UnknownType
    property string source

    property bool selected: false

    signal setActiveVideo(int videoId)

    function remove() {
        if (selected) setActiveVideo(0);
        presenter.remove();
    }

    onVideoIdChanged: presenter.setVideo(videoId)

    deepEnabled: false
    implicitWidth: col.implicitWidth + industrial.margins * 2
    implicitHeight: col.implicitHeight + industrial.margins * 2

    menuItems: [
        Controls.MenuItem {
            text: qsTr("Remove")
            iconSource: "qrc:/icons/remove.svg"
            iconColor: industrial.colors.negative
            onTriggered: videoView.remove()
        }
    ]

    VideoSourcePresenter{
        id: presenter
        view: videoView
    }

    ColumnLayout {
        id: col
        anchors.fill: parent
        anchors.margins: industrial.margins
        anchors.rightMargin: videoView.margin
        spacing: industrial.spacing

        Controls.RadioButton {
            checked: videoView.selected
            text: qsTr("Video") + " " + videoId
            horizontalAlignment: Text.AlignHCenter
            Controls.ButtonGroup.group: radioGroup
            onCheckedChanged: if (checked) setActiveVideo(videoId)
            Layout.fillWidth: true
        }

        Controls.Label {
            id: typeLabel
            text: {
                var str = qsTr("Type");
                switch (type) {
                case VideoSource.Stream: return str + ": " + qsTr("Stream video")
                case VideoSource.Device: return str + ": " + qsTr("Device")
                case VideoSource.UnknownType:
                default: return str + ": " + qsTr("Unknown")
                }
            }
            Layout.fillWidth: true
        }

        Controls.TextField {
            visible: type == VideoSource.Stream
            labelText: qsTr("Stream URL")
            text: source
            onEditingFinished: {
                presenter.setSource(text);
                if (videoView.selected) video.updateActiveVideo();
            }
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            visible: type == VideoSource.Device
            labelText: qsTr("Device file")
            model: videoDevices
            currentIndex: videoDevices.indexOf(source);
            onActivated: {
                presenter.setSource(displayText);
                if (videoView.selected) video.updateActiveVideo();
            }
            Layout.fillWidth: true
        }
    }
}
