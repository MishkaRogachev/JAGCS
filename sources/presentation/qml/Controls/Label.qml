import QtQuick 2.6
import QtQuick.Templates 2.0 as T

T.Label {
    id: control

    // TODO: fix dynamic width calculation
    font.pixelSize: sizings.fontPixelSize
    color: palette.textColor
    verticalAlignment: Qt.AlignVCenter
    elide: Text.ElideRight
    wrapMode: Text.WordWrap
}
