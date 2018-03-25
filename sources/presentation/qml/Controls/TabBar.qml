import QtQuick 2.6
import QtQuick.Controls 2.2 as T

T.TabBar { // TODO: replace with model-based bar
    id: control

    implicitWidth: sizings.controlBaseSize * count * 6
    implicitHeight: sizings.controlBaseSize

    background: Rectangle {
        color: customPalette.backgroundColor
    }
}
