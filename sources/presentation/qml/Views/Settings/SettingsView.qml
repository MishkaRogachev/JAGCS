import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

import "Communications"
import "Vehicles"
import "Video"

Controls.Pane {
    id: root

    signal makeDefaults()

    RowLayout {
        anchors.fill: parent

        ColumnLayout {

            Controls.ButtonBar {
                id: bar
                anchors.top: parent.top
                model: [
                    qsTr("Communications"),
                    qsTr("Vehicles"),
                    qsTr("Video"),
                    qsTr("GUI"),
                    qsTr("Networking"),
                    qsTr("About")
                ]
            }

            Item {
                Layout.fillHeight: true
            }

            Controls.Button {
                text: qsTr("Make defaults")
                Layout.preferredWidth: bar.width
                onClicked: makeDefaults()
            }
        }

        StackLayout {
            height: parent.height
            currentIndex: bar.currentIndex

            CommunicationSettingsView { objectName: "communications" }
            VehicleSettingsView { objectName: "vehicles" }
            VideoSettingsView { objectName: "video" }
            GuiSettingsView { objectName: "gui" }
            NetworkSettingsView { objectName: "network" }
            AboutView { objectName: "about" }
        }
    }
}
