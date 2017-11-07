import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout { // TODO: to common menu
    id: column

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
            highlighted: loader.sourceComponent === modelData.comp
            onClicked: if (modelData.component) reqestComponent(modelData.component, text)
            Layout.fillWidth: true
        }
    }
}
