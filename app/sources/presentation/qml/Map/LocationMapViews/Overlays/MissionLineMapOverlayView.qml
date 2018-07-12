import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

MapItemView {
    delegate: MapPolyline {
        line.width: sizings.controlBaseSize / 8
        line.color: {
            switch (missionStatus) {
            case MissionAssignment.Actual:
                return customPalette.missionColor;
            case MissionAssignment.Downloading:
            case MissionAssignment.Uploading:
                return customPalette.cautionColor;
            case MissionAssignment.NotActual:
                return customPalette.dangerColor;
            default:
                return customPalette.backgroundColor;
            }
        }
        path: missionPath
        z: 10
    }
}
