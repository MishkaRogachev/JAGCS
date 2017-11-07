import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

import "About"

ColumnLayout { // TODO: to common menu
    id: column

    signal reqestComponent(Component component, string text)

    property  var menuModel:  [
        { text: qsTr("Data Base") },
        { text: qsTr("Communications") },
        { text: qsTr("Vehicles") },
        { text: qsTr("Video") },
        { text: qsTr("Settings"), menu: [
                { text: qsTr("Map") },
                { text: qsTr("Joystick") },
                { text: qsTr("GUI") },
                { text: qsTr("Networking") }
            ] },
        { text: qsTr("About"), component: aboutComponent },
        { text: qsTr("Quit") }
    ]

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

    Component {
        id: aboutComponent

        AboutView { objectName: "about" }
    }
}
