import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Pane {
    id: root

    TabBar {
        id: bar
        width: parent.width

        TabButton { text: qsTr("User interface") }
        TabButton { text: qsTr("Network settings") }
    }

    StackLayout {
        anchors.top: bar.bottom
        width: parent.width
        currentIndex: bar.currentIndex

        GuiSettingsView { id: uiTab }
        NetworkSettingsView { id: networkSettings }
    }
}
