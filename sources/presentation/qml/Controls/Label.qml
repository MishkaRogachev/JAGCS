import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Label {
    id: control

    property alias iconSource: icon.source

    font.pixelSize: palette.fontPixelSize
    color: palette.textColor

    Image {
        id: icon
        anchors.verticalCenter: parent.verticalCenter
    }
}
