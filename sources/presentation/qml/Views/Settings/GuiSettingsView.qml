import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property alias uiSize: uiSlider.value

    signal setUiSize(int uiSize)

    ColumnLayout{
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: qsTr("UI size")
            }

            Slider {
                id: uiSlider
                Layout.fillWidth: true
                from: 24
                to: 64
                onPressedChanged: if (!pressed) setUiSize(value);
            }

            Label {
                Layout.preferredWidth: 86
                horizontalAlignment: Text.AlignHCenter
                text: uiSlider.value.toFixed(0)
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
