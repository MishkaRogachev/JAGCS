import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property var videoSources

    signal addDeviceVideo()
    signal addStreamVideo()

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: column.height
        clip: true

        ScrollBar.vertical: ScrollBar {}

        Controls.Frame {
            visible: repeater.count == 0
            width: parent.width
            height: label.height + palette.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No video sources present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            anchors.centerIn: parent
            spacing: palette.spacing

            Repeater {
                id: repeater
                model: videoSources

                VideoSourceView {
                    id: sourceView
                    Layout.fillWidth: true
                    Component.onCompleted: modelData.setView(sourceView)
                }
            }
        }
    }

    Controls.Button {
        id: addButton
        Layout.fillWidth: true
        text: qsTr("Add video source")
        iconSource: "qrc:/icons/add.svg"
        anchors.right: parent.right
        onClicked: if (!addMenu.visible) addMenu.open()

        Controls.Menu {
            id: addMenu
            implicitWidth: parent.width
            y: parent.height

            Controls.MenuItem {
                text: qsTr("Device")
                implicitWidth: parent.width
                onTriggered: addDeviceVideo()
            }

            Controls.MenuItem {
                text: qsTr("Stream")
                implicitWidth: parent.width
                onTriggered: addStreamVideo()
            }
        }
    }
}
