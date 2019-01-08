import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

MapItemView {
    delegate: MapPolyline {
        line.width: industrial.baseSize / 8
        line.color: {
            switch (missionStatus) {
            case MissionAssignment.Actual:
                return industrial.colors.highlight;
            case MissionAssignment.Downloading:
            case MissionAssignment.Uploading:
                return industrial.colors.caution;
            case MissionAssignment.NotActual:
                return industrial.colors.danger;
            default:
                return industrial.colors.background;
            }
        }
        path: missionPath
        z: 10
    }
}
