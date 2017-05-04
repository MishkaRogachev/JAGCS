import QtQuick 2.6
import QtQuick.Controls 2.0

import "qrc:/JS/helper.js" as Helper
import "./"

RealSpinBox {
    id: control

    property bool isLongitude: false

    stepSize: 0.000277777777778
    from: isLongitude ? -180 : -90
    to: isLongitude ? 180 : 90

    contentItem: TextInput {
        id: input
        focus: true
        text: Helper.degreesToDmsString(value, isLongitude)
        onEditingFinished: value =  Helper.dmsStringToDegree(text, isLongitude)
        font: control.font
        color: palette.textColor
        selectionColor: palette.selectionColor
        selectedTextColor: palette.selectedTextColor
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        validator: RegExpValidator {
            regExp: /[0-9]{1,3}[°][0-9]{1,2}['][0-9]{1,2}[.][0-9]{1,2}"[N,S,W,E]/
        }
    }
}
