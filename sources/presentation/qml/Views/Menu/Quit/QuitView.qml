import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    spacing: palette.spacing

    Controls.Button {
        text: qsTr("Quit")
        iconSource: "qrc:/icons/quit.svg"
        onClicked: Qt.quit()
        Layout.preferredWidth: palette.controlBaseSize * 7
        Layout.fillWidth: true
    }
}
