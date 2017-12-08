import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Frame {
    id: control

    property color backgroundColor: palette.raisedColor

    background:  Rectangle {
        color: backgroundColor
        radius: 3

        Shadow {
            source: parent
        }
    }
}
