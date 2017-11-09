import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    implicitWidth: palette.controlBaseSize * 7
    spacing: palette.spacing

    Controls.Button {
        text: qsTr("Quit")
        iconSource: "qrc:/icons/quit.svg"
        onClicked: Qt.quit()
        Layout.fillWidth: true
    }
}
