import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Label {
    id: control

    // TODO: fix dynamic width calculation
    font.pixelSize: palette.fontPixelSize
    color: palette.textColor
    verticalAlignment: Qt.AlignVCenter
    elide: Text.ElideRight
}
