import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    padding: 0

    Flickable {
        anchors.fill: parent
        implicitWidth: content.width
        contentHeight: content.height
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Item {
            id: content
            width: column.width
            height: Math.max(root.height, column.implicitHeight)

            ColumnLayout {
                id: column
                anchors.centerIn: parent
                height: parent.height
                spacing: palette.spacing

                Controls.ButtonBar {
                    id: bar
                    anchors.top: parent.top
                    currentIndex: -1
                    model: [
                        qsTr("Data Base"),
                        qsTr("Communications"),
                        qsTr("Vehicles"),
                        qsTr("Video"),

                        qsTr("Map"),
                        qsTr("Joystick"),
                        qsTr("GUI"),
                        qsTr("Networking"),
                        qsTr("About")
                    ]
                }

                Controls.Button {
                    text: qsTr("Exit")
                    iconSource: "qrc:/icons/quit.svg"
                    iconColor: palette.dangerColor
                    onClicked: Qt.quit()
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignBottom
                }
            }
        }
    }
}
