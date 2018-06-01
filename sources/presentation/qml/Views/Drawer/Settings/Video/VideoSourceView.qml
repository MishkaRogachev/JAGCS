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
    implicitWidth: grid.implicitWidth + sizings.margins * 2
    implicitHeight: grid.implicitHeight + sizings.margins * 2

    VideoSourcePresenter{
        id: presenter
        view: videoView
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        anchors.margins: sizings.margins
        anchors.rightMargin: videoView.margin
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.RadioButton {
            checked: videoView.selected
            text: qsTr("Video") + " " + videoId
            horizontalAlignment: Text.AlignHCenter
            Controls.ButtonGroup.group: radioGroup
            onCheckedChanged: if (checked) setActiveVideo(videoId)
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Type")
            Layout.fillWidth: true
        }

        Controls.Label {
            id: typeLabel
            text: {
                switch (type) {
                case VideoSource.Stream: return qsTr("Stream video")
                case VideoSource.Device: return qsTr("Device")
                default: return qsTr("Unknown")
                }
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: {
                switch (type) {
                case VideoSource.Stream: return qsTr("Stream URL:")
                case VideoSource.Device: return qsTr("Device file:")
                default: return qsTr("Unknown:")
                }
            }
            Layout.fillWidth: true
        }

        Controls.TextField {
            visible: type == VideoSource.Stream
            text: source
            placeholderText: qsTr("Enter stream url")
            onEditingFinished: presenter.setSource(text)
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            visible: type == VideoSource.Device
            model: videoDevices
            currentIndex: videoDevices.indexOf(source);
            onActivated: presenter.setSource(text)
            Layout.fillWidth: true
        }
    }
}
