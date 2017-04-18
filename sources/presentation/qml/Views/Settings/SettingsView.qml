import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "Communications"

Pane {
    id: root

    signal makeDefaults()

    RowLayout {
        anchors.fill: parent

        ColumnLayout {

            ButtonBar {
                id: bar
                anchors.top: parent.top
                model: [
                    qsTr("GUI"),
                    qsTr("Communications"),
                    qsTr("Video"),
                    qsTr("Networking"),
                    qsTr("About")
                ]
            }

            Item {
                Layout.fillHeight: true
            }

            Button {
                text: qsTr("Make defaults")
                Layout.preferredWidth: palette.controlBaseWidth
                onClicked: makeDefaults()
            }
        }

        StackLayout {
            height: parent.height
            currentIndex: bar.currentIndex

            GuiSettingsView { objectName: "gui" }
            CommunicationsView { objectName: "communications" }
            VideoSettingsView { objectName: "video" }
            NetworkSettingsView { objectName: "network" }
            AboutView { objectName: "about" }
        }
    }
}
