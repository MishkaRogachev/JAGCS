import QtQuick 2.6

import "qrc:/JS/helper.js" as Helper

SpinBox {
    id: control

    property real realValue: NaN
    property real realFrom: 0
    property real realTo: 100
    property real precision: 0.01

    to: realTo / precision
    from: realFrom / precision
    isValid: false

    Component.onCompleted: recalc()
    onRealValueChanged: recalc()
    onValueChanged: realValue = value * precision

    validator: DoubleValidator {
        bottom: Math.min(control.from * precision, control.to * precision)
        top: Math.max(control.from * precision, control.to * precision)
    }

    textFromValue: function(value, locale) {
        return Number(value * precision).toLocaleString(locale, 'f', Helper.decimals(precision))
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text) / precision
    }

    function recalc() {
        if (!isNaN(realValue)) {
            isValid = true;
            value = Math.round(realValue / precision);
        }
        else isValid = false;
    }
}
