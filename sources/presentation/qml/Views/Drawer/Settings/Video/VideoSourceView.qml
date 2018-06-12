import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

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
    // onDeepIn: TODO: edit video
    Component.onCompleted: {
        //menu.addEntry(qsTr("Edit"), "qrc:/icons/edit.svg").triggered.connect(edit);

        var removeItem = menu.addEntry(qsTr("Remove"), "qrc:/icons/remove.svg");
        removeItem.iconColor = customPalette.dangerColor;
        removeItem.triggered.connect(videoView.remove);
    }

    deepEnabled: false
    implicitWidth: col.implicitWidth + sizings.margins * 2
    implicitHeight: col.implicitHeight + sizings.margins * 2

    VideoSourcePresenter{
        id: presenter
        view: videoView
    }

    ColumnLayout {
        id: col
        anchors.fill: parent
        anchors.margins: sizings.margins
        anchors.rightMargin: videoView.margin
        spacing: sizings.spacing

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
