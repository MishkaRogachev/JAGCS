import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "../../Video"

Controls.Frame {
    id: root

    property int type: VideoSource.UnknownType
    property string source
    property bool changed: false
    property bool videoVisible: false

    signal save()
    signal restore()
    signal remove()

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
                Layout.fillWidth: true
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
                iconSource: videoVisible ? "qrc:/ui/show.svg" : "qrc:/ui/hide.svg"
                onClicked: videoVisible = !videoVisible
            }
        }

        VideoView {
            objectName: "preview"
            visible: videoVisible
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
                iconColor: palette.negativeColor
            }
        }
    }
}
