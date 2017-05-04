import QtQuick 2.6
import QtQuick.Controls 2.0

import "./" as Custom

SpinBox {
    id: control

    contentItem: Custom.TextField {
        z: 2
        text: control.textFromValue(control.value, control.locale)
        font: control.font
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }
}
