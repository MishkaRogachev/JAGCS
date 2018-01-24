import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: videoSource

    property int videoId: -1
    property int type: VideoSource.UnknownType
    property string source

    property bool selected: false
    property bool changed: false

    signal setActiveVideo(int videoId)

    VideoSourcePresenter{
        id: presenter
        view: videoSource
        Component.onCompleted: setVideo(videoId)
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2
        rowSpacing: sizings.spacing
        columnSpacing: sizings.spacing

        Controls.Label {
            text: qsTr("Video") + " " + videoId
            Layout.fillWidth: true
        }

        Controls.RadioButton {
            checked: videoSource.selected
            Controls.ButtonGroup.group: radioGroup
            onCheckedChanged: if (checked) setActiveVideo(videoId)
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
            onTextChanged: {
                source = text;
                changed = true;
            }
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            visible: type == VideoSource.Device
            model: videoDevices
            currentIndex: videoDevices.indexOf(source);
            onDisplayTextChanged: {
                source = displayText;
                changed = true;
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Actions")
        }

        RowLayout {
            Controls.Button {
                tipText: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: presenter.save()
                enabled: changed
            }

            Controls.Button {
                tipText: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: presenter.updateView()
                enabled: changed
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onActivated: {
                    if (selected) setActiveVideo(-1);
                    presenter.remove();
                }
                iconColor: palette.dangerColor
            }
        }
    }
}
