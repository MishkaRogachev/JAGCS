import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root
    spacing: sizings.spacing

    Controls.Label {
        text: qsTr("Realy quit?")
        Layout.alignment: Qt.AlignHCenter
    }

    Controls.Button {
        text: qsTr("Yes")
        iconSource: "qrc:/icons/quit.svg"
        iconColor: customPalette.dangerColor
        flat: true
        onClicked: Qt.quit()
        Layout.fillWidth: true
    }

    Controls.Button {
        text: qsTr("No")
        iconSource: "qrc:/icons/remove.svg"
        flat: true
        onClicked: menu.home()
        Layout.fillWidth: true
    }

    Item {
        Layout.fillHeight: true
    }
}
