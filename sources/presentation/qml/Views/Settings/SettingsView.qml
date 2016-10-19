import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"
import "Connection"

Pane {
    id: root

    property QtObject presenter: factory.createSettingsPresenter(root)

    RowLayout {
        anchors.fill: parent

        ButtonBar {
            id: bar
            anchors.top: parent.top
            model: [ qsTr("User interface"), qsTr("Connection"),
                     qsTr("Video"), qsTr("Network settings") ]
        }

        StackLayout {
            height: parent.height
            currentIndex: bar.currentIndex

            GuiSettingsView { id: ui}

            ConnectionSettingsView {
                id: connection
                Component.onCompleted: {
                    presenter.createConnectionSettings(connection);
                }
            }

            VideoSettingsView {
                id: video
                presenter: root.presenter.createVideoSettings(video)
            }

            NetworkSettingsView {
                id: network
                presenter: root.presenter.createNetworkSettings(network)
            }
        }
    }
}
