import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"
import "Connection"

Pane {
    id: root

    signal makeDefaults()

    RowLayout {
        anchors.fill: parent

        ColumnLayout {

            ButtonBar {
                id: bar
                anchors.top: parent.top
                model: [ qsTr("User interface"), qsTr("Connection"),
                    qsTr("Video"), qsTr("Network settings") ]
            }

            Item {
                Layout.fillHeight: true
            }

            Button {
                text: qsTr("Make defaults")
                Layout.fillWidth: true
                onClicked: makeDefaults()
            }
        }

        StackLayout {
            height: parent.height
            currentIndex: bar.currentIndex

            GuiSettingsView { objectName: "ui" }
            ConnectionSettingsView { objectName: "connections" }
            VideoSettingsView { objectName: "video" }
            NetworkSettingsView { objectName: "network" }
        }
    }
}
