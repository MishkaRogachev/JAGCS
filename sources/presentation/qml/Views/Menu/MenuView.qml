import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    padding: 0

    Flickable {
        anchors.fill: parent
        implicitWidth: column.width
        contentHeight: column.height
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        ColumnLayout {
            id: column
            implicitHeight: root.height
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

            Item {
                Layout.fillHeight: true
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
