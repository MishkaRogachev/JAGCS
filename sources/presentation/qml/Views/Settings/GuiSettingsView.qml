import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property alias fullscreen: fullscreenBox.checked
    property alias locales: languageBox.model
    property alias localeIndex: languageBox.currentIndex
    property alias uiSize: uiSlider.value
    property alias paletteStyle: paletteBar.currentIndex
    property alias fdRollInverted: fdRollBar.currentIndex
    property int speedStep: 0
    property int altitudeStep: 0

    signal updateSettings()

    onSpeedStepChanged: speedBox.currentIndex = speedBox.model.indexOf(speedStep)
    onAltitudeStepChanged: altitudeBox.currentIndex = altitudeBox.model.indexOf(altitudeStep)

    GridLayout {
        anchors.fill: parent
        anchors.margins: palette.controlBaseSize / 2
        rowSpacing: palette.controlBaseSize / 2
        columns: 3

        Label {
            text: qsTr("Fullscreen")
            Layout.fillWidth: true
        }

        CheckBox {
            id: fullscreenBox
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignRight
            onCheckedChanged: {
                updateSettings();
                main.updateUiSettings();
            }
        }

        Label {
            text: qsTr("Language")
            Layout.fillWidth: true
        }

        ComboBox {
            id: languageBox
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentIndexChanged: updateSettings()
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
                updateSettings();
                main.updateUiSettings();
            }
        }

        Label {
            Layout.preferredWidth: 86
            horizontalAlignment: Text.AlignHCenter
            text: uiSlider.visualValue.toFixed(0)  // TODO: current value
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
                    updateSettings();
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
            text: qsTr("Artificial horizon")
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
                onCurrentIndexChanged: updateSettings()

                TabButton {
                    text: qsTr("Western")
                }
                TabButton {
                    text: qsTr("Russian")
                }
            }
        }

        Label {
            text: qsTr("Speed scale step")
            Layout.fillWidth: true
        }

        ComboBox {
            id: speedBox
            model: [5, 10, 25, 50, 100]
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentTextChanged: {
                speedStep = currentText;
                updateSettings();// changed = true;
            }
        }

        Label {
            text: qsTr("Altitude scale step")
            Layout.fillWidth: true
        }

        ComboBox {
            id: altitudeBox
            model: [5, 10, 25, 50, 100]
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentTextChanged: {
                altitudeStep = currentText;
                updateSettings();// changed = true;
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
