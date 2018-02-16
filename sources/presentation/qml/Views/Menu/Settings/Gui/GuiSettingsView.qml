import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

GridLayout {
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

    columns: 2
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    GuiSettingsPresenter {
        id: presenter
        view: gui
        Component.onCompleted: updateView()
    }

    Controls.Label {
        text: qsTr("Fullscreen")
    }

    Controls.CheckBox {
        id: fullscreenBox
        onCheckedChanged: {
            presenter.setFullscreen(checked);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Language")
    }

    Controls.ComboBox {
        id: languageBox
        Layout.fillWidth: true
        onCurrentIndexChanged: {
            presenter.setLocale(currentIndex);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("UI size")
    }

    Controls.ComboBox {
        id: uiSizeBox
        model: [24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64]
        Layout.fillWidth: true
        onDisplayTextChanged: {
            uiSize = displayText;
            presenter.setUiSize(uiSize);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Palette")
    }

    Controls.ComboBox {
        id: paletteBox
        model: [ qsTr("Outdoor"), qsTr("Indoor") ]
        Layout.fillWidth: true
        onCurrentIndexChanged: {
            presenter.setPalleteStyle(currentIndex);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Artificial horizon")
    }

    Controls.ComboBox {
        id: rollBar
        model: [ qsTr("Western"), qsTr("Russian") ]
        Layout.fillWidth: true
        onCurrentIndexChanged: {
            dashboard.rollInverted = currentIndex;
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Speed scale step")
    }

    Controls.ComboBox {
        id: speedBox
        model: [5, 10, 25, 50, 100]
        Layout.fillWidth: true
        onDisplayTextChanged: {
            speedStep = displayText;
            dashboard.speedStep = speedStep;
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Speed units")
    }

    Controls.ComboBox {
        id: speedUnitsBox
        model: availableSpeedUnits
        Layout.fillWidth: true
        onCurrentIndexChanged: {
            dashboard.speedUnits = presenter.speedUnitFromIndex(currentIndex);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Altitude scale step")
    }

    Controls.ComboBox {
        id: altitudeBox
        model: [5, 10, 25, 50, 100]
        Layout.fillWidth: true
        onDisplayTextChanged: {
            altitudeStep = displayText;
            dashboard.altitudeStep = altitudeStep;
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Altitude units")
    }

    Controls.ComboBox {
        id: altitudeUnitsBox
        model: availableAltitudeUnits
        Layout.fillWidth: true
        onCurrentIndexChanged: {
            dashboard.altitudeUnits = presenter.altitudeUnitFromIndex(currentIndex);
            changed = true;
        }
    }

    Controls.Label {
        text: qsTr("Relative altitude")
    }

    Controls.CheckBox {
        id: relativeAltitudeBox
        onCheckedChanged: {
            dashboard.altitudeRelative = checked;
            changed = true;
        }
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
    }

    RowLayout {
        spacing: sizings.spacing
        Layout.columnSpan: 2

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: presenter.updateView()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: presenter.save()
            enabled: changed
            Layout.fillWidth: true
        }
    }
}
