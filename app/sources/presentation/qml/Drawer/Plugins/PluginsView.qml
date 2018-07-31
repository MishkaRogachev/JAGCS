import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

ColumnLayout {
    id: plugins

    property var discoveredPlugins

    spacing: sizings.spacing

    PluginsPresenter {
        id: presenter
        view: plugins
    }

    RowLayout {
        Item {
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/refresh.svg"
            tipText: qsTr("Refresh plugins")
            flat: true
            onClicked: presenter.discoverPlugins();
        }
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

        delegate: RowLayout {
            width: list.width
            spacing: sizings.spacing

            Controls.CheckBox {
                text: model.pluginName
                tipText: model.pluginDescription
                checked: model.pluginEnabled
                Layout.fillWidth: true
            }

            Controls.Label {
                text: model.pluginVersion
                Layout.fillWidth: true
            }
        }
    }
}
