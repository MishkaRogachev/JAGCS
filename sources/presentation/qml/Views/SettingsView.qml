import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Pane {
    TabBar {
        id: bar
        width: parent.width

        TabButton { text: qsTr("User interface") }
        TabButton { text: qsTr("Network settings") }
    }

    StackLayout {
        width: parent.width
        currentIndex: bar.currentIndex

        Item {
            id: uiTab
        }

        Item {
            id: networkSettings
        }
    }
}
