import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Item {
    id: root

    property var videoSources
    property var videoDevices: []

    signal addDeviceVideo()
    signal addStreamVideo()

    implicitWidth: palette.controlBaseSize * 11

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: addButton.height
        contentHeight: Math.max(frame.height, column.height)
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            id: frame
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
            anchors.centerIn: parent
            width: parent.width
            spacing: palette.spacing

            Repeater {
                id: repeater
                model: videoSources

                VideoSourceView {
                    id: sourceView
                    number: index + 1
                    Layout.fillWidth: true
                    Component.onCompleted: modelData.setView(sourceView)
                }
            }
        }
    }

    Controls.Button {
        id: addButton
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        text: qsTr("Add video source")
        iconSource: "qrc:/icons/add.svg"
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

