import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

MapItemView {
    delegate: MapQuickItem {
        coordinate: position

        Behavior on coordinate {
            CoordinateAnimation { duration: 200 }
        }

        sourceItem: Rectangle {
            width: 32 // TODO: map point size
            height: width
            radius: width / 2
            color: palette.missionColor
        }

        Label {
            text: seq
            anchors.centerIn: parent
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
