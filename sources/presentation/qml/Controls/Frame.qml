import QtQuick 2.6
import QtQuick.Controls 2.0 as T

T.Frame {
    id: control

    property color backgroundColor: palette.raisedColor

    background: Item {

        Rectangle {
            id: rect
            anchors.fill: parent
            color: backgroundColor
            radius: 3
            visible: false
        }

        Shadow {
            anchors.fill: rect
            source: rect
        }
    }
}
