import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    padding: 0

    ColumnLayout {
        anchors.fill: parent

        Controls.Button {
            flat: true
            text: qsTr("Exit")
            iconSource: "qrc:/icons/quit.svg"
            iconColor: palette.dangerColor
            onClicked: Qt.quit()
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom
        }
    }
}
