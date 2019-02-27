import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

ColumnLayout {
    id: root
    spacing: industrial.spacing

    Controls.Label {
        text: qsTr("Realy quit?")
        Layout.alignment: Qt.AlignHCenter
    }

    Controls.Button {
        text: qsTr("Yes")
        iconSource: "qrc:/icons/quit.svg"
        iconColor: industrial.colors.negative
        flat: true
        onClicked: Qt.quit()
        Layout.fillWidth: true
    }

    Controls.Button {
        text: qsTr("No")
        iconSource: "qrc:/icons/remove.svg"
        flat: true
        onClicked: drawer.home()
        Layout.fillWidth: true
    }

    Item {
        Layout.fillHeight: true
    }
}
