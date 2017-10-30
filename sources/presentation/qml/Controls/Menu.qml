import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Menu {
    id: control

    background: Rectangle {
        implicitWidth: palette.controlBaseSize * 6
        implicitHeight: palette.controlBaseSize
        color: palette.raisedColor
    }
}
