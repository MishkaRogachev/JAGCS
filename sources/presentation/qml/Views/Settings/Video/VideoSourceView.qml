import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../../Video"

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

    RowLayout {
        anchors.fill: parent
        spacing: palette.spacing

        GridLayout {
            columns: 3
            rowSpacing: palette.spacing
            columnSpacing: palette.spacing

            Controls.Label {
                text: qsTr("Video") + " " + number
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.Button {
                iconSource: preview.visible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
                onClicked: preview.visible = !preview.visible
                Layout.alignment: Qt.AlignRight
            }

            Controls.Label {
                text: qsTr("Type")
                Layout.columnSpan: 2
                Layout.fillWidth: true
            }

            Controls.Label {
                text: {
                    switch (type) {
                    case VideoSource.Stream: return qsTr("Stream video")
                    case VideoSource.Device: return qsTr("Device")
                    default: return qsTr("Unknown:")
                    }
                }
                Layout.alignment: Qt.AlignRight
            }

            Controls.Label {
                text: {
                    switch (type) {
                    case VideoSource.Stream: return qsTr("Stream URL:")
                    case VideoSource.Device: return qsTr("Device file:")
                    default: return qsTr("Unknown:")
                    }
                }
            }

            Controls.TextField {
                visible: type == VideoSource.Stream
                text: source
                placeholderText: qsTr("Enter stream url")
                Layout.columnSpan: 2
                Layout.fillWidth: true
                onTextChanged: {
                    source = text;
                    changed = true;
                }
            }

            Controls.ComboBox {
                visible: type == VideoSource.Device
                model: videoDevices
                Layout.columnSpan: 2
                Layout.fillWidth: true
                currentIndex: videoDevices.indexOf(source);
                onCurrentTextChanged: {
                    source = currentText;
                    changed = true;
                }
            }

            Controls.Button {
                text: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: restore()
                enabled: changed
                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: save()
                enabled: changed
                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onClicked: remove()
                iconColor: palette.dangerColor
                Layout.fillWidth: true
            }
        }

        VideoView {
            id: preview
            visible: false
            onVisibleChanged: visible ? setupPreview(preview) : setupPreview(null)
            Layout.fillHeight: true
            implicitWidth: height / ratio
        }
    }
}

    /*
    ColumnLayout {
        anchors.fill: parent
        spacing: palette.spacing

        RowLayout {

            Controls.Label {
                text: {
                    switch (type) {
                    case VideoSource.Stream: return qsTr("URL:")
                    case VideoSource.Device: return qsTr("Device:")
                    default: return qsTr("Unknown:")
                    }
                }
                c
            }

            Controls.TextField {
                visible: type == VideoSource.Stream
                text: source
                placeholderText: qsTr("Enter stream url")
                Layout.fillWidth: true
                onTextChanged: {
                    source = text;
                    changed = true;
                }
            }

            Controls.ComboBox {
                visible: type == VideoSource.Device
                model: videoDevices
                Layout.fillWidth: true
                currentIndex: videoDevices.indexOf(source);
                onCurrentTextChanged: {
                    source = currentText;
                    changed = true;
                }
            }

            Controls.Button {
                iconSource: preview.visible ? "qrc:/ui/show.svg" : "qrc:/ui/hide.svg"
                onClicked: preview.visible = !preview.visible
            }
        }

        VideoView {
            id: preview
            visible: false
            onVisibleChanged: visible ? setupPreview(preview) : setupPreview(null)
            implicitWidth: controlsRow.width
            Layout.alignment: Qt.AlignRight
        }

        RowLayout {
            id: controlsRow
            Layout.alignment: Qt.AlignRight

            Controls.Button {
                text: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: restore()
                enabled: changed
            }

            Controls.Button {
                text: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: save()
                enabled: changed
            }

            Controls.Button {
                text: qsTr("Remove")
                iconSource: "qrc:/icons/remove.svg"
                onClicked: remove()
                iconColor: palette.dangerColor
            }
        }
    }
}*/
