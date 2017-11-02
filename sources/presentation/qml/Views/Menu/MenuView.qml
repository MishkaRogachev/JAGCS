import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Menu {
    id: root

    title: qsTr("Menu")

    Controls.MenuItem {
        text: qsTr("About")
    }

    Controls.MenuItem {
        text: qsTr("Exit")
        iconSource: "qrc:/icons/quit.svg"
        iconColor: palette.dangerColor
        onTriggered: Qt.quit()
    }
}
