import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Frame {
    id: root

//    property QtObject presenter: factory.createGuiSettingsPresenter(root)

    ColumnLayout{
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("Toolbar width")
            }

            Slider {
                id: sidebarWidthSlider
                Layout.fillWidth: true
                value: settingsProvider.value("Gui/toolbarWidth");
                from: 80
                to: 640
                onPressedChanged: {
                    if (!pressed) settingsProvider.setValue("Gui/toolbarWidth", value);
                }
            }

            Label {
                Layout.preferredWidth: 86
                horizontalAlignment: Text.AlignHCenter
                text: sidebarWidthSlider.value.toFixed(0)
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
