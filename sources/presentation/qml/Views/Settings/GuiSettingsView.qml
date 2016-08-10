import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

//    property QtObject presenter: factory.createGuiSettingsPresenter(root)

    GridLayout {
        columns: 2
        anchors.fill: parent

        Label {
            text: qsTr("Toolbar width")
        }

        RowLayout {

            Slider {
                id: sidebarWidthSlider
                value: settingsProvider.value("Gui/toolbarWidth");
                from: 80
                to: 640
                onPressedChanged: {
                    if (!pressed) settingsProvider.setValue("Gui/toolbarWidth", value);
                }
            }

            Label {
                text: sidebarWidthSlider.value.toFixed(0)
            }
        }
    }
}
