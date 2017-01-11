import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Button {
    id: root

    property var model

    signal triggered(var data)
    onClicked: menu.open()

    Menu {
        id: menu
        y: root.height

        Instantiator {
            model: root.model

            MenuItem {
                text: modelData
                width: menu.width
                onTriggered: {
                    root.triggered(modelData);
                    menu.close();
                }
            }
            onObjectAdded: menu.insertItem(index, object)
            onObjectRemoved: menu.removeItem(object)
        }
    }
}
