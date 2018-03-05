import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Templates 2.0 as T

import "../Shaders" as Shaders
import "../JS/helper.js" as Helper
import "./" as Controls

T.Control {
    id: control

    property real value: 0
    property bool isLongitude: false
    property int secondsPrecision: 2

    readonly property bool isValid: !isNaN(value)
    readonly property real scalingFactor: width / implicitWidth

    property int sign: 1
    property Item focusedItem

    function updateValueFromControls() {
        console.log("updateValueFromControls -- ?");
        value = Helper.dmsToDegree(sign,
                                   Math.abs(dInput.text),
                                   Math.abs(mInput.text),
                                   Helper.stringToReal(sInput.text, locale.decimalPoint));
    }

    function updateControlsFromValue() {
        console.log("updateControlsFromValue -- ok", value);
        if (isValid) {
            var dms = Helper.degreesToDms(value, isLongitude, secondsPrecision);
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
    implicitWidth: row.implicitWidth
    implicitHeight: sizings.controlBaseSize

    background: Rectangle {
        anchors.fill: parent
        radius: 3
        color: isValid ? palette.sunkenColor : palette.dangerColor
        border.color: scope.activeFocus ? palette.highlightColor : "transparent"

        Shaders.Hatch {
            anchors.fill: parent
            color: palette.sunkenColor
            visible: !control.enabled
        }
    }

    contentItem: FocusScope {
        id: scope
        focus: true
        activeFocusOnTab: true
        anchors.fill: parent

        RowLayout {
            id: row
            anchors.fill: parent
            spacing: 1

            Controls.Button {
                Layout.minimumWidth: sizings.controlBaseSize
                flat: true
                autoRepeat: true
                iconSource: "qrc:/ui/minus.svg"
                onClicked: {
                    if (!scope.activeFocus) {
                        dInput.forceActiveFocus();
                    }
                    else {
                        if (focusedItem) focusedItem.decreaseValue();
                    }
                }
            }

            NumericInput {
                id: dInput
                focus: true
                maximumLength: isLongitude ? 3 : 2
                nextItem: mInput
                validator: IntValidator {
                    top: isLongitude ? 180 : 90
                    bottom: 0
                }
                onIncreaseValue: changeValue(0, 1)
                onDecreaseValue: changeValue(0, -1)
                Layout.preferredWidth: sizings.controlBaseSize * (isLongitude ? 1 : 0.75)
                Layout.fillWidth: true
            }

            Controls.Label { text: "\u00B0" }

            NumericInput {
                id: mInput
                maximumLength: 2
                previousItem: dInput
                nextItem: sInput
                validator: IntValidator {
                    top: 60
                    bottom: 0
                }
                onIncreaseValue: changeValue(1, 1)
                onDecreaseValue: changeValue(1, -1)
                Layout.preferredWidth: sizings.controlBaseSize * 0.75
                Layout.fillWidth: true
            }

            Controls.Label { text: "\'" }

            NumericInput {
                id: sInput
                maximumLength: 3 + secondsPrecision
                previousItem: mInput
                validator: DoubleValidator {
                    bottom: 0
                    top: 60
                }
                onIncreaseValue: changeValue(2, Math.pow(10, -secondsPrecision))
                onDecreaseValue: changeValue(2, -Math.pow(10, -secondsPrecision))
                Layout.preferredWidth: sizings.controlBaseSize * (0.75 + secondsPrecision / 5 * 2)
                Layout.fillWidth: true
            }

            Controls.Label { text: "\"" }

            Button {
                flat: true
                text: sign < 0 ? isLongitude ? qsTr("W") : qsTr("S") : isLongitude ?
                                                   qsTr("E") : qsTr("N")
                onClicked: {
                    value = -value;
                    updateControlsFromValue();
                }
            }

            Controls.Button {
                Layout.minimumWidth: sizings.controlBaseSize
                flat: true
                autoRepeat: true
                iconSource: "qrc:/ui/plus.svg"
                onClicked: {
                    if (!scope.activeFocus) {
                        dInput.forceActiveFocus();
                    }
                    else {
                        if (focusedItem) focusedItem.increaseValue();
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
        color: scope.activeFocus ? palette.highlightColor : "transparent"
        Behavior on x { NumberAnimation { duration: 150 } }
    }
}
