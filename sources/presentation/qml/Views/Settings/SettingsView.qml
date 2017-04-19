import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "Communications"
import "Vehicles"

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

            Button {
                text: qsTr("Make defaults")
                Layout.preferredWidth: palette.controlBaseWidth
                onClicked: makeDefaults()
            }
        }

        StackLayout {
            height: parent.height
            currentIndex: bar.currentIndex

            CommunicationsView { objectName: "communications" }
            VehiclesView { objectName: "vehicles" }
            VideoSettingsView { objectName: "video" }
            GuiSettingsView { objectName: "gui" }
            NetworkSettingsView { objectName: "network" }
            AboutView { objectName: "about" }
        }
    }
}
