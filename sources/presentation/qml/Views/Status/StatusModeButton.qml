import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Controls.Button {
    id: root

    property string mode

    onClicked: if (!highlighted) setMode(mode)
    highlighted: main.mode === mode
    flat: true
}
