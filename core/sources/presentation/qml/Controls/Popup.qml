import QtQuick 2.6
import QtQuick.Controls 2.2 as T

import "./"

T.Popup {
    id: control

    property color backgroundColor: customPalette.backgroundColor

    background:  Rectangle {
        color: backgroundColor
        radius: 2

        Shadow {
            source: parent
        }
    }
}
