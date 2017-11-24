import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Menu {
    id: control

    background: Rectangle {
        implicitWidth: sizings.controlBaseSize * 6
        implicitHeight: sizings.controlBaseSize
        color: palette.raisedColor
    }
}
