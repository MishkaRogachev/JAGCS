import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

ColumnLayout {

    Button {
        iconSource: "qrc:/icons/home.svg"
        checkable: true
        anchors.horizontalCenter: parent.horizontalCenter
        checked: settingHome
        onClicked: settingHome = !settingHome
    }
}
