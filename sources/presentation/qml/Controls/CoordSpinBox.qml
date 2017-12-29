import QtQuick 2.6

import "qrc:/JS/helper.js" as Helper

RealSpinBox {
    id: control

    property bool isLongitude: false
    property bool dmsFormat: settings.boolValue("Gui/coordinatesDms")

    // FIXME: fix formula
    from: isLongitude ? (-180 / precision) : (-90 / precision)
    to: isLongitude ? (180 / precision) : (90 / precision)
    precision: dmsFormat ? Helper.dmsToDegree(1, 0, 0, 0.01) : 0.000001

    validator: RegExpValidator {
        regExp: dmsFormat ?
                    /[0-9]{1,3}[°][0-9]{1,2}['][0-9]{1,2}[.][0-9]{1,2}"[N,S,W,E]/ :
                    /^[0-9]+(\\.[0-9]+)?$/
    }

    textFromValue: function(value, locale) {
        return dmsFormat ? Helper.degreesToDmsString(value * precision, isLongitude) :
                           Helper.degreesToString(value * precision, 6);
    }

    valueFromText: function(text, locale) {
        return dmsFormat ? Helper.dmsStringToDegree(text, isLongitude) / precision :
                           Helper.stringToDegree(text / precision);
    }
}
