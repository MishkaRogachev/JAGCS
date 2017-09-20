import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

import "DataBase"
import "Communications"
import "Vehicles"
import "Video"
import "Map"
import "Joystick"
import "Gui"
import "Network"
import "Help"

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

            Item { Layout.fillHeight: true }

            Controls.Button {
                text: qsTr("Make defaults")
                Layout.preferredWidth: bar.width
                onClicked: makeDefaults()
            }
        }

        StackLayout {
            height: parent.height
            currentIndex: bar.currentIndex

            DataBaseView { objectName: "dataBase" }
            CommunicationSettingsView { objectName: "communications" }
            VehicleSettingsView { objectName: "vehicles" }
            VideoSettingsView { objectName: "video" }
            MapSettingsView { objectName: "map" }
            JoystickSettingsView{ objectName: "joystick" }
            GuiSettingsView { objectName: "gui" }
            NetworkSettingsView { objectName: "network" }
            AboutView { objectName: "about" }
        }
    }
}
