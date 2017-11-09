import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: control

    property var menuModel

    signal reqestComponent(Component component, string text)

    function home() {
        repeater.model = menuModel;
    }

    spacing: palette.spacing

    Repeater {
        id: repeater
        model: menuModel

        Controls.Button {
            text: modelData.text ? modelData.text : ""
            iconSource: modelData.icon ? modelData.icon : ""
            iconColor: modelData.iconColor ? modelData.iconColor : iconColor
            onClicked: {
                if (modelData.component) reqestComponent(modelData.component, text);
                if (modelData.menu) repeater.model = modelData.menu;
            }
            Layout.preferredWidth: palette.controlBaseSize * 7
            Layout.fillWidth: true
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
