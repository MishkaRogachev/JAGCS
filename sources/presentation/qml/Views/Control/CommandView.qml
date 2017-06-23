import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

RowLayout {
    id: root

    Controls.Button {
        text: qsTr("Commands")
        onClicked: menu.open()
        Layout.alignment: Qt.AlignRight

        Controls.Menu {
            id: menu
            y: parent.height

            Controls.MenuItem {
                text: qsTr("Arm/Disarm")
            }
        }
    }
}
