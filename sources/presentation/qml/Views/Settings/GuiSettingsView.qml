import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property alias locales: languageBox.model
    property alias localeIndex: languageBox.currentIndex
    property alias uiSize: uiSlider.value
    property alias paletteStyle: paletteBar.currentIndex
    property alias fdPitchInverted: fdPitchBar.currentIndex
    property alias fdRollInverted: fdRollBar.currentIndex

    signal updateSettings()

    GridLayout {
        anchors.fill: parent
        anchors.margins: palette.controlBaseSize / 2
        rowSpacing: palette.controlBaseSize / 2
        columns: 3

        Label {
            text: qsTr("Language")
            Layout.fillWidth: true
        }

        ComboBox {
            id: languageBox
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentIndexChanged: root.updateSettings();
        }

        Label {
            text: qsTr("UI size")
            Layout.fillWidth: true
        }

        Slider {
            id: uiSlider
            from: 24
            to: 64
            Layout.fillWidth: true
            onPressedChanged: {
                if (pressed) return;
                root.updateSettings();
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
            text: qsTr("Palette")
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            height: paletteBar.height

            TabBar {
                id: paletteBar
                anchors.centerIn: parent
                width: parent.width
                onCurrentIndexChanged: {
                    root.updateSettings();
                    main.updateUiSettings();
                }

                TabButton {
                    text: qsTr("Outdoor")
                }
                TabButton {
                    text: qsTr("Indoor")
                }
            }
        }

        Label {
            text: qsTr("Flight director pitch view")
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            height: fdPitchBar.height

            TabBar {
                id: fdPitchBar
                anchors.centerIn: parent
                width: parent.width
                onCurrentIndexChanged: root.updateSettings();

                TabButton {
                    text: qsTr("From Plane")
                }
                TabButton {
                    text: qsTr("From ground")
                }
            }
        }

        Label {
            text: qsTr("Flight director roll view")
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            height: fdRollBar.height

            TabBar {
                id: fdRollBar
                anchors.centerIn: parent
                width: parent.width
                onCurrentIndexChanged: root.updateSettings();

                TabButton {
                    text: qsTr("From Plane")
                }
                TabButton {
                    text: qsTr("From ground")
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
