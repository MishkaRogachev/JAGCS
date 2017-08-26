import QtQuick 2.6

import "qrc:/JS/helper.js" as Helper

RealSpinBox {
    id: control

    property bool isLongitude: false
    from: isLongitude ? (-180 / precision) : (-90 / precision)
    to: isLongitude ? (180 / precision) : (90 / precision)
    precision: 0.00001

    validator: RegExpValidator {
        regExp: /[0-9]{1,3}[°][0-9]{1,2}['][0-9]{1,2}[.][0-9]{1,2}"[N,S,W,E]/
    }

    textFromValue: function(value, locale) {
        return Helper.degreesToDmsString(value * precision, isLongitude);
    }

    valueFromText: function(text, locale) {
        return Helper.dmsStringToDegree(text, isLongitude) / precision;
    }
}
