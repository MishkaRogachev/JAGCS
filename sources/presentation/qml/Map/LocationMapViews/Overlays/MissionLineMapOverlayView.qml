import QtQuick 2.6
import QtLocation 5.6
import QtPositioning 5.6
import JAGCS 1.0

import Industrial.Indicators 1.0 as Indicators

MapItemView {
    delegate: MapPolyline {
        line.width: industrial.baseSize / 8
        line.color: {
            switch (missionStatus) {
            case MissionAssignment.Actual:
                return industrial.colors.highlight;
            case MissionAssignment.Downloading:
            case MissionAssignment.Uploading:
                return Indicators.Theme.cautionColor;
            case MissionAssignment.NotActual:
                return Indicators.Theme.dangerColor;
            default:
                return Indicators.Theme.backgroundColor;
            }
        }
        path: missionPath
        z: 10
    }
}
