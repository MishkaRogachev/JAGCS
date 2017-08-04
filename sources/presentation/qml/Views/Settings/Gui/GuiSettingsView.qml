import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property bool changed: false
    property int speedStep: 0
    property int altitudeStep: 0

    property alias fullscreen: fullscreenBox.checked
    property alias locales: languageBox.model
    property alias localeIndex: languageBox.currentIndex
    property alias uiSize: uiSlider.value
    property alias paletteStyle: paletteBar.currentIndex
    property alias fdRollInverted: fdRollBar.currentIndex
    property alias relativeAltitude: relativeAltitudeBox.checked

    signal save()
    signal restore()

    onSpeedStepChanged: speedBox.currentIndex = speedBox.model.indexOf(speedStep)
    onAltitudeStepChanged: altitudeBox.currentIndex = altitudeBox.model.indexOf(altitudeStep)

    GridLayout {
        anchors.fill: parent
        rowSpacing: palette.spacing
        columns: 3

        Controls.Label {
            text: qsTr("Fullscreen")
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: fullscreenBox
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignRight
            onCheckedChanged: changed = true
        }

        Controls.Label {
            text: qsTr("Language")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: languageBox
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentIndexChanged: changed = true
        }

        Controls.Label {
            text: qsTr("UI size")
            Layout.fillWidth: true
        }

        Controls.Slider {
            id: uiSlider
            from: 24
            to: 64
            Layout.fillWidth: true
            onPressedChanged:  if (!pressed) changed = true
        }

        Controls.Label {
            Layout.preferredWidth: 86
            horizontalAlignment: Text.AlignHCenter
            text: uiSlider.visualValue.toFixed(0)  // TODO: current value
        }

        Controls.Label {
            text: qsTr("Palette")
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            height: paletteBar.height

            Controls.TabBar {
                id: paletteBar
                anchors.centerIn: parent
                width: parent.width
                onCurrentIndexChanged: changed = true

                Controls.TabButton {
                    text: qsTr("Outdoor")
                }
                Controls.TabButton {
                    text: qsTr("Indoor")
                }
            }
        }

        Controls.Label {
            text: qsTr("Artificial horizon")
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
            Layout.columnSpan: 2
            height: fdRollBar.height

            Controls.TabBar {
                id: fdRollBar
                anchors.centerIn: parent
                width: parent.width
                onCurrentIndexChanged: changed = true

                Controls.TabButton {
                    text: qsTr("Western")
                }
                Controls.TabButton {
                    text: qsTr("Russian")
                }
            }
        }

        Controls.Label {
            text: qsTr("Speed scale step")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: speedBox
            model: [5, 10, 25, 50, 100]
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentTextChanged: {
                speedStep = currentText;
                changed = true;
            }
        }

        Controls.Label {
            text: qsTr("Altitude scale step")
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: altitudeBox
            model: [5, 10, 25, 50, 100]
            Layout.columnSpan: 2
            Layout.fillWidth: true
            onCurrentTextChanged: {
                altitudeStep = currentText;
                changed = true;
            }
        }

        Controls.Label {
            text: qsTr("Relative altitude")
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: relativeAltitudeBox
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignRight
            onCheckedChanged: changed = true
        }

        Item {
            Layout.fillHeight: true
            Layout.columnSpan: 3
        }

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: {
                save();
                main.updateUiSettings();
            }
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
