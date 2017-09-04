import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

MapItemView {
    delegate: MapPolyline {
        line.width: 6
        line.color: {
            switch (missionStatus) {
            case MissionAssignment.Actual:
                return palette.missionColor;
            case MissionAssignment.Downloading:
            case MissionAssignment.Uploading:
                return palette.cautionColor;
            case MissionAssignment.NotActual:
                return palette.dangerColor;
            default:
                return palette.backgroundColor;
            }
        }
        path: missionPath
    }
}
