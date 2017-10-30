import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Rectangle {
    id: root

    color: palette.raisedColor
    height: palette.controlBaseSize

    RowLayout {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        Controls.Button {
            tipText: qsTr("Quit")
            iconSource: "qrc:/icons/quit.svg"
            iconColor: palette.dangerColor
            anchors.verticalCenter: parent.verticalCenter
            onClicked: Qt.quit()
        }
    }
}
