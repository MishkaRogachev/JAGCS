import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

ColumnLayout {
    id: plugins
    spacing: sizings.spacing

    property var discoveredPlugins

    PluginsPresenter {
        id: presenter
        view: plugins
        Component.onCompleted: updatePlugins()
    }

    Controls.Label {
        text: qsTr("Plugins")
        Layout.alignment: Qt.AlignHCenter
    }

    ListView {
        id: list
        model: discoveredPlugins
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        Layout.fillWidth: true
        Layout.fillHeight: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        Controls.Label {
            text: "test"
            Layout.fillWidth: true
        }
    }
}
