import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Button {
    id: root

    property alias model: repeater.model

    signal triggered(var data)

    enabled: repeater.count > 0
    onClicked: menu.open()

    Menu {
        id: menu
        y: root.height

        Repeater {
            id: repeater

            MenuItem {
                text: modelData
                width: menu.width
                onTriggered: root.triggered(modelData)
            }
        }
    }
}
