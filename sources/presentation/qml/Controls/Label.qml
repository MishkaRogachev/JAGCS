import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Label {
    id: control

    property alias iconSource: icon.source

    Image {
        id: icon
        anchors.verticalCenter: parent.verticalCenter
    }

    font.pointSize: palette.fontSize
    color: palette.textColor
}
