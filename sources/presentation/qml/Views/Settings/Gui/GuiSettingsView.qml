import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property bool changed: false
    property int speedStep: 0
    property int altitudeStep: 0

    property alias fullscreen: fullscreenBox.checked
    property alias locales: languageBox.model
    property alias localeIndex: languageBox.currentIndex
    property alias uiSize: uiSlider.value
    property alias paletteStyle: paletteBar.currentIndex
    property alias rollInverted: rollBar.currentIndex
    property alias speedUnits: speedUnitsBox.currentIndex
    property alias relativeAltitude: relativeAltitudeBox.checked
    property alias coordinatesDms: coordinatesDmsBox.checked

    signal save()
    signal restore()

    onSpeedStepChanged: speedBox.currentIndex = speedBox.model.indexOf(speedStep)
    onAltitudeStepChanged: altitudeBox.currentIndex = altitudeBox.model.indexOf(altitudeStep)

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: frame.height
        clip: true

        ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            id: frame
            width: root.width

            GridLayout {
                anchors.fill: parent
                rowSpacing: palette.spacing
                columns: 2

                Controls.Label {
                    text: qsTr("Fullscreen")
                }

                Controls.CheckBox {
                    id: fullscreenBox
                    onCheckedChanged: changed = true
                }

                Controls.Label {
                    text: qsTr("Language")
                }

                Controls.ComboBox {
                    id: languageBox
                    Layout.fillWidth: true
                    onCurrentIndexChanged: changed = true
                }

                Controls.Label {
                    text: qsTr("UI size")
                }

                RowLayout {

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
                        text: uiSlider.visualValue.toFixed(0)
                    }
                }

                Controls.Label {
                    text: qsTr("Palette")
                }

                Item {
                    Layout.fillWidth: true
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
                }

                Item {
                    Layout.fillWidth: true
                    height: rollBar.height

                    Controls.TabBar {
                        id: rollBar
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
                }

                Controls.ComboBox {
                    id: speedBox
                    model: [5, 10, 25, 50, 100]
                    Layout.fillWidth: true
                    onCurrentTextChanged: {
                        speedStep = currentText;
                        changed = true;
                    }
                }

                Controls.Label {
                    text: qsTr("Speed units")
                }

                Controls.ComboBox {
                    id: speedUnitsBox
                    model: [ qsTr("mps"), qsTr("kph") ]
                    Layout.fillWidth: true
                    onCurrentIndexChanged: changed = true;
                }

                Controls.Label {
                    text: qsTr("Altitude scale step")
                }

                Controls.ComboBox {
                    id: altitudeBox
                    model: [5, 10, 25, 50, 100]
                    Layout.fillWidth: true
                    onCurrentTextChanged: {
                        altitudeStep = currentText;
                        changed = true;
                    }
                }

                Controls.Label {
                    text: qsTr("Relative altitude")
                }

                Controls.CheckBox {
                    id: relativeAltitudeBox
                    onCheckedChanged: changed = true
                }

                Controls.Label {
                    text: qsTr("Coordinates in DMS")
                }

                Controls.CheckBox {
                    id: coordinatesDmsBox
                    onCheckedChanged: changed = true
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }

    RowLayout {
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
            onClicked: save()
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
