import QtQuick 2.6
import QtQuick.Controls 2.0
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

    property alias currentSettings: bar.currentIndex

    signal requestPresenter(string view)

    RowLayout {
        anchors.fill: parent

        Flickable {
            Layout.fillHeight: true
            implicitWidth: column.width
            contentHeight: column.height
            clip: true

            ScrollBar.vertical: Controls.ScrollBar {}

            ColumnLayout {
                id: column

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
            }
        }

        Loader {
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: {
                switch (currentSettings) {
                case 0: return dataBaseComponent;
                case 1: return communicationsComponent;
                case 2: return vehiclesComponent;
                case 3: return videoComponent;
                case 4: return mapComponent;
                case 5: return joystickComponent;
                case 6: return guiComponent;
                case 7: return networkComponent;
                case 8: return aboutComponent;
                default:
                    return null;
                }
            }
        }

        Component { id : dataBaseComponent; DataBaseView { objectName: "dataBase";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : communicationsComponent; CommunicationSettingsView { objectName: "communications";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : vehiclesComponent; VehicleSettingsView { objectName: "vehicles";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : videoComponent; VideoSettingsView { objectName: "video";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : mapComponent; MapSettingsView { objectName: "map";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : joystickComponent; JoystickSettingsView { objectName: "joystick";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : guiComponent; GuiSettingsView { objectName: "gui";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : networkComponent; NetworkSettingsView { objectName: "network";
                Component.onCompleted: requestPresenter(objectName) } }
        Component { id : aboutComponent; AboutView { objectName: "about";
                Component.onCompleted: requestPresenter(objectName) } }
    }
}
