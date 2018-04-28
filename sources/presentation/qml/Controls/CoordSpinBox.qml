import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Templates 2.2 as T

import "../Shaders" as Shaders
import "../JS/helper.js" as Helper

T.Control {
    id: control

    property real value: 0
    property bool isLongitude: false
    property color color: customPalette.textColor
    property int secondsPrecision: 2
    property int sign: 1

    readonly property bool isValid: !isNaN(value)
    readonly property real scalingFactor: width / implicitWidth

    property Item focusedItem

    function updateValueFromControls() {
        value = Helper.dmsToDegree(sign,
                                   Math.abs(dInput.text),
                                   Math.abs(mInput.text),
                                   Helper.stringToReal(sInput.text, locale.decimalPoint));
    }

    function updateControlsFromValue() {
        if (isValid) {
            var dms = Helper.degreesToDms(value, isLongitude, secondsPrecision);
            sign = dms.sign;
            dInput.text = Helper.pad(dms.deg, dInput.maximumLength);
            mInput.text = Helper.pad(dms.min, mInput.maximumLength);
            sInput.text = Helper.padReal(dms.sec, 2, secondsPrecision, locale.decimalPoint);
        }
        else {
            dInput.text = Helper.pad(0, dInput.maximumLength);
            mInput.text = Helper.pad(0, mInput.maximumLength);
            sInput.text = Helper.padReal(0, 2, secondsPrecision, locale.decimalPoint);
        }
    }

    function changeValue(digit, add) {
        if (!isValid) {
            value = 0;
            return;
        }

        var dms = Helper.degreesToDms(value, isLongitude, secondsPrecision);

        switch (digit) {
        case 0:
            dms.deg = +dms.deg + add;
            break;
        case 1:
            dms.min = +dms.min + add;
            break;
        case 2:
            dms.sec = +dms.sec + add;
            break;
        }

        value = Helper.dmsToDegree(dms.sign, dms.deg, dms.min, dms.sec);
    }

    Component.onCompleted: updateControlsFromValue()
    onValueChanged: updateControlsFromValue()

    clip: true
    opacity: enabled ? 1 : 0.33
    implicitWidth: row.implicitWidth
    implicitHeight: sizings.controlBaseSize
    font.pixelSize: sizings.fontPixelSize

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: isValid ? customPalette.sunkenColor : customPalette.dangerColor
        border.color: scope.activeFocus ? customPalette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: customPalette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: FocusScope {
        id: scope
        activeFocusOnTab: true
        anchors.fill: parent

        RowLayout {
            id: row
            anchors.fill: parent
            spacing: 1

            Button {
                flat: true
                autoRepeat: true
                activeFocusOnTab: false
                visible: enabled
                iconColor: control.isValid ? control.color : customPalette.selectedTextColor
                iconSource: "qrc:/ui/minus.svg"
                pressedImpl: focusedItem && focusedItem.down
                onClicked: {
                    if (focusedItem) {
                        if (focusedItem.activeFocus) focusedItem.forceActiveFocus();
                        focusedItem.decreaseValue();
                    }
                    else {
                        dInput.forceActiveFocus();
                    }
                }
            }

            CoordSpinBoxInput {
                id: dInput
                focus: true
                font: control.font
                color: control.isValid ? control.color : customPalette.selectedTextColor
                maximumLength: isLongitude ? 3 : 2
                nextItem: mInput
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator { bottom: 0; top: isLongitude ? 180 : 90 }
                onIncreaseValue: changeValue(0, 1)
                onDecreaseValue: changeValue(0, -1)
                Layout.preferredWidth: sizings.controlBaseSize * (isLongitude ? 1 : 0.75)
                Layout.fillWidth: true
            }

            Label {
                font: control.font
                color: control.isValid ? control.color : customPalette.selectedTextColor
                text: "\u00B0"
            }

            CoordSpinBoxInput {
                id: mInput
                font: control.font
                color: control.isValid ? control.color : customPalette.selectedTextColor
                maximumLength: 2
                previousItem: dInput
                nextItem: sInput
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator { bottom: 0; top: 60 }
                onIncreaseValue: changeValue(1, 1)
                onDecreaseValue: changeValue(1, -1)
                Layout.preferredWidth: sizings.controlBaseSize * 0.75
                Layout.fillWidth: true
            }

            Label {
                font: control.font
                color: control.isValid ? control.color : customPalette.selectedTextColor
                text: "\'"
            }

            CoordSpinBoxInput {
                id: sInput
                font: control.font
                color: control.isValid ? control.color : customPalette.selectedTextColor
                maximumLength: 3 + secondsPrecision
                previousItem: mInput
                inputMethodHints: Qt.ImhFormattedNumbersOnly
                validator: DoubleValidator { bottom: 0; top: 60 }
                onIncreaseValue: changeValue(2, Math.pow(10, -secondsPrecision))
                onDecreaseValue: changeValue(2, -Math.pow(10, -secondsPrecision))
                Layout.preferredWidth: sizings.controlBaseSize * (0.75 + secondsPrecision / 5 * 2)
                Layout.fillWidth: true
            }

            Label {
                font: control.font
                color: control.isValid ? control.color : customPalette.selectedTextColor
                text: "\""
            }

            Button {
                flat: true
                font: control.font
                activeFocusOnTab: false
                textColor: control.isValid ? control.color : customPalette.selectedTextColor
                text: sign < 0 ? (isLongitude ? qsTr("W") : qsTr("S")) :
                                 (isLongitude ? qsTr("E") : qsTr("N"))
                onClicked: {
                    value = -value;
                    updateControlsFromValue();
                }
            }

            Button {
                flat: true
                autoRepeat: true
                activeFocusOnTab: false
                visible: enabled
                iconColor: control.isValid ? control.color : customPalette.selectedTextColor
                iconSource: "qrc:/ui/plus.svg"
                pressedImpl: focusedItem && focusedItem.up
                onClicked: {
                    if (focusedItem) {
                        if (focusedItem.activeFocus) focusedItem.forceActiveFocus();
                        focusedItem.increaseValue();
                    }
                    else {
                        dInput.forceActiveFocus();
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.bottom: control.bottom
        width: focusedItem ? focusedItem.width + 5 : 0
        height: control.height * 0.1
        x: focusedItem ? focusedItem.x : 0
        color: scope.activeFocus ? customPalette.highlightColor : "transparent"
        Behavior on x { NumberAnimation { duration: 150 } }
    }
}
