import QtQuick 2.6
import QtQuick.Layouts 1.3

ColumnLayout {
    id: control

    property var menuModel

    signal reqestComponent(string source, string text, var properties)

    function home() {
        repeater.model = menuModel;
    }

    spacing: sizings.spacing

    Repeater {
        id: repeater
        model: menuModel

        Button {
            text: modelData.text ? modelData.text : ""
            iconSource: modelData.icon ? modelData.icon : ""
            iconColor: modelData.iconColor ? modelData.iconColor : customPalette.textColor
            flat: true
            onClicked: {
                if (modelData.source) {
                    reqestComponent(modelData.source, text,
                                    modelData.properties ? modelData.properties : {});

                }
                else if (modelData.menu) {
                    repeater.model = modelData.menu;
                }
            }
            contentWidth: width - sizings.controlBaseSize
            implicitWidth: sizings.controlBaseSize * 7
            Layout.fillWidth: true
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
