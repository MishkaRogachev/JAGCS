import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

MapView {
    id: root

    property var vehicleModel

    signal setHome(var coordinate)

    property bool settingHome: false

    MapItemView {
        model: vehicleModel
        delegate: MapPolyline {
            line.width: 4
            line.color: palette.trackColor
            path: track
            smooth: true
        }
    }

    MapItemView {
        model: vehicleModel
        delegate: MapQuickItem {
            anchorPoint.x: homeImage.width / 2
            anchorPoint.y: homeImage.height / 2
            coordinate: homePosition

            sourceItem: Image {
                id: homeImage
                source: "qrc:/indicators/home_mark.svg"
            }
        }
    }

    MapItemView {
        model: vehicleModel
        autoFitViewport: true
        delegate: MapQuickItem {
            coordinate: position

            sourceItem: Item {
                id: markItem

                ColoredIcon {
                    id: markImage
                    anchors.centerIn: parent
                    rotation: direction
                    source: mark
                }

                Label {
                    text: vehicleId
                    anchors.centerIn: parent
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            if (settingHome) {
                setHome(root.toCoordinate(Qt.point(mouseX, mouseY), true));
                settingHome = false;
            }
        }
    }

    MapActions {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 7
    }
}
