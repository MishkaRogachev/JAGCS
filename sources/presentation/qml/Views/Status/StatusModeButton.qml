import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Button {
    id: root

    property string mode

    onClicked: setMode(mode)
    checked: main.mode == mode
    enabled: !checked
}
