import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.TabBar {
    id: control

    implicitWidth: palette.controlBaseSize * count * 6
    implicitHeight: palette.controlBaseSize

    background: Rectangle {
        color: palette.backgroundColor
    }
}
