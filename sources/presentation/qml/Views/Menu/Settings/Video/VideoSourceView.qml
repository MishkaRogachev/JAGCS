import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property int number: 0
    property int type: VideoSource.UnknownType
    property string source
    property bool changed: false

    signal save()
    signal restore()
    signal remove()
    signal setupPreview(QtObject preview)

    implicitHeight: grid.height + palette.margins * 2

    GridLayout {
        id: grid
        anchors.centerIn: parent
        width: parent.width - palette.margins * 2
        columns: 2
        rowSpacing: palette.spacing
        columnSpacing: palette.spacing

        Controls.Label {
            text: qsTr("Video") + " " + number
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
                default: return qsTr("Unknown:")
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
            onCurrentTextChanged: {
                source = currentText;
                changed = true;
            }
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.columnSpan: 2

            Controls.Button {
                tipText: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: save()
                enabled: changed
            }

            Controls.Button {
                tipText: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: restore()
                enabled: changed
            }

            Controls.DelayButton {
                tipText: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onActivated: remove()
                iconColor: palette.dangerColor
            }
        }
    }
}
