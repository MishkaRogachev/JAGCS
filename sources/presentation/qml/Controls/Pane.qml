import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Pane {
    id: control

    background: Item {

        Rectangle {
            id: rect
            anchors.fill: parent
            color: palette.backgroundColor
            visible: false
        }

        Shadow {
            anchors.fill: rect
            source: rect
        }
    }

    /*
    Item {
            id: dataObject
            width: contentItem.width
            height: contentItem.height

            Rectangle {
                id: back
                color: palette.sunkenColor
                anchors.fill: parent
            }

            DropShadow {
                id: shadow
                visible: shadows
                anchors.fill: back
                source: back
                verticalOffset: 7
                radius: 25
                samples: 2 * radius + 1
                color: palette.shadowColor
            }
        }*/
}
