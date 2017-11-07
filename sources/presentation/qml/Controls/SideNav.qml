import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: control

    signal reqestComponent(Component component, string text)

    property var menuModel

    spacing: palette.spacing

    Repeater {
        id: repeater
        model: menuModel

        Controls.Button {
            text: modelData.text ? modelData.text : ""
            iconSource: modelData.icon ? modelData.icon : ""
            iconColor: modelData.iconColor ? modelData.iconColor : iconColor
            onClicked: if (modelData.component) reqestComponent(modelData.component, text)
            Layout.fillWidth: true
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
