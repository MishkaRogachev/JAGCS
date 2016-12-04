import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtLocation 5.6
import QtPositioning 5.6

import "qrc:/Controls"

import "../Map"
import "../Video"

Pane {
    id: root

    property var missionModel

    VehicleMapView { // TODO: separate MissionMapView/Overlay
        objectName: "map"
        anchors.fill: parent

        MapItemView {
            model: missionModel
            delegate: MapPolyline {
                line.width: 6
                line.color: palette.missionColor
                path: missionLine
                smooth: true
            }
        }
    }
}
