import QtQuick 2.6
import QtQuick.Templates 2.2 as T

T.Label {
    id: control

    font.pixelSize: sizings.fontSize
    color: customPalette.textColor
    verticalAlignment: Text.AlignVCenter
    elide: Text.ElideRight
}
