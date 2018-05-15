import QtQuick 2.6
import QtQuick.Layouts 1.3

import "../../Controls" as Controls

ColumnLayout {
    id: menu

    property alias menuModel: repeater.model

    spacing: sizings.spacing

    Repeater {
        id: repeater

        Controls.Button {
            text: modelData.text ? modelData.text : ""
            iconSource: modelData.icon ? modelData.icon : ""
            flat: true
            onClicked: menuModel[index].action()
            contentWidth: width - sizings.controlBaseSize
            implicitWidth: sizings.controlBaseSize * 7
            Layout.fillWidth: true
        }
    }

    Item { Layout.fillHeight: true }
}
