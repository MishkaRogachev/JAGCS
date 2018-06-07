import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

Item {
    id: gui

    property bool changed: false

    property var availableSpeedUnits
    property var availableAltitudeUnits

    property int uiSize: 0
    property int speedStep: 0
    property int altitudeStep: 0

    property alias fullscreen: fullscreenBox.checked
    property alias locales: languageBox.model
    property alias localeIndex: languageBox.currentIndex
    property alias paletteStyle: paletteBox.currentIndex
    property alias rollInverted: rollBar.currentIndex
    property alias speedUnits: speedUnitsBox.currentIndex
    property alias relativeAltitude: relativeAltitudeBox.checked
    property alias altitudeUnits: altitudeUnitsBox.currentIndex
    property alias coordinatesDms: coordinatesDmsBox.checked

    onUiSizeChanged: uiSizeBox.currentIndex = uiSizeBox.model.indexOf(uiSize)
    onSpeedStepChanged: speedBox.currentIndex = speedBox.model.indexOf(speedStep)
    onAltitudeStepChanged: altitudeBox.currentIndex = altitudeBox.model.indexOf(altitudeStep)
    Component.onDestruction: if (changed) presenter.updateView()

    implicitWidth: Math.max(contents.implicitWidth, buttons.implicitWidth)

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: buttons.height
        contentHeight: contents.height
        boundsBehavior: Flickable.OvershootBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        ColumnLayout {
            id: contents
            width: parent.width
            spacing: sizings.spacing

            GuiSettingsPresenter {
                id: presenter
                view: gui
                Component.onCompleted: updateView()
            }

            Controls.CheckBox {
                id: fullscreenBox
                text: qsTr("Fullscreen")
                onCheckedChanged: {
                    presenter.setFullscreen(checked);
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: languageBox
                labelText: qsTr("Language")
                onCurrentIndexChanged: {
                    presenter.setLocale(currentIndex);
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: uiSizeBox
                labelText: qsTr("UI size")
                model: [24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64]
                onDisplayTextChanged: {
                    uiSize = displayText;
                    presenter.setUiSize(uiSize);
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: paletteBox
                labelText: qsTr("Palette")
                model: [ qsTr("Night"), qsTr("Day") ]
                onCurrentIndexChanged: {
                    presenter.setPalleteStyle(currentIndex);
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: rollBar
                labelText: qsTr("Artificial horizon")
                model: [ qsTr("Western"), qsTr("Russian") ]
                onCurrentIndexChanged: {
                    dashboard.rollInverted = currentIndex;
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: speedBox
                labelText: qsTr("Speed scale step")
                model: [5, 10, 25, 50, 100]
                onDisplayTextChanged: {
                    speedStep = displayText;
                    dashboard.speedStep = speedStep;
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: speedUnitsBox
                labelText: qsTr("Speed units")
                model: availableSpeedUnits
                onCurrentIndexChanged: {
                    dashboard.speedUnits = presenter.speedUnitFromIndex(currentIndex);
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: altitudeBox
                labelText: qsTr("Altitude scale step")
                model: [5, 10, 25, 50, 100]
                onDisplayTextChanged: {
                    altitudeStep = displayText;
                    dashboard.altitudeStep = altitudeStep;
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: altitudeUnitsBox
                labelText: qsTr("Altitude units")
                model: availableAltitudeUnits
                onCurrentIndexChanged: {
                    dashboard.altitudeUnits = presenter.altitudeUnitFromIndex(currentIndex);
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.CheckBox {
                id: relativeAltitudeBox
                text: qsTr("Relative altitude")
                onCheckedChanged: {
                    dashboard.altitudeRelative = checked;
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.CheckBox {
                id: coordinatesDmsBox
                text: qsTr("Coordinates in DMS")
                onCheckedChanged: changed = true
                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    SaveRestore {
        id: buttons
        anchors.bottom: parent.bottom
        width: parent.width
        enabled: changed
        onSave: presenter.save()
        onRestore: presenter.updateView()
    }
}
