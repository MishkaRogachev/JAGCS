import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: button

    flat: true
    implicitWidth: sizings.controlBaseSize * 0.75
    implicitHeight: sizings.controlBaseSize * 0.75
}
