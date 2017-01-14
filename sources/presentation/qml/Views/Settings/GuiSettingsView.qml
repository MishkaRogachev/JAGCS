import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property alias uiSize: uiSlider.value
    property alias paletteStyle: paletteBar.currentIndex

    signal setUiSize(int uiSize)
    signal setPaletteStyle(int paletteStyle)

    GridLayout{
        anchors.fill: parent
        columns: 3

        Label {
            Layout.fillWidth: true
            text: qsTr("UI size")
        }

        Slider {
            id: uiSlider
            Layout.fillWidth: true
            from: 24
            to: 64
            onPressedChanged: {
                if (pressed) return;
                root.setUiSize(value);
                main.updateUiSettings();
            }
        }

        Label {
            Layout.preferredWidth: 86
            horizontalAlignment: Text.AlignHCenter
            text: (uiSlider.from + uiSlider.position *
                   (uiSlider.to - uiSlider.from)).toFixed(0)  // TODO: current value
        }

        Label {
            Layout.fillWidth: true
            text: qsTr("Palette")
        }

        TabBar {
            id: paletteBar
            Layout.fillWidth: true
            onCurrentIndexChanged: {
                root.setPaletteStyle(currentIndex);
                main.updateUiSettings();
            }

            TabButton {
                text: qsTr("Indoor")
            }
            TabButton {
                text: qsTr("Outdoor")
            }
        }

        Item { width: 1; height: 1 } // TODO: placeholder item

        Item {
            Layout.fillHeight: true
        }
    }
}
