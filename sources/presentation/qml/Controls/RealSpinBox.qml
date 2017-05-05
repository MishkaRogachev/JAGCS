import QtQuick 2.6
import QtQuick.Controls 2.0

import "./" as Custom
import "qrc:/JS/helper.js" as Helper

Custom.SpinBox {
    id: control

    property real realValue: NaN
    property real realFrom: 0
    property real realTo: 100
    property real precision: 0.01

    to: realTo / precision
    from: realFrom / precision
    onRealValueChanged: value = realValue / precision
    onValueChanged: realValue = value * precision

    validator: DoubleValidator {
        bottom: Math.min(control.from * precision, control.to * precision)
        top: Math.max(control.from * precision, control.to * precision)
    }

    textFromValue: function(value, locale) {
        return Number(value * precision).toLocaleString(
                    locale, 'f', Helper.decimals(precision))
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text) / precision
    }
}
