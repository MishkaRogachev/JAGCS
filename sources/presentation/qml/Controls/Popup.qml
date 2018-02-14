import QtQuick 2.6
import QtQuick.Controls 2.0 as T

import "./"

T.Popup {
    id: control

    property color backgroundColor: palette.backgroundColor

    background:  Rectangle {
        color: backgroundColor
        radius: 2

        Shadow {
            source: parent
        }
    }
}
