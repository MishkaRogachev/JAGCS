import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

AbstractVehicleView {
    id: root

    property real indicatedAirSpeed
    property int throttle

    property real barometric_altitude
    property real barometric_climb

    signal minimize()

    contentWidth: column.implicitWidth
    contentHeight: column.implicitHeight

    ColumnLayout {
        id: column
        anchors.fill: parent

        Controls.Label {
            text: qsTr("MAV") + ": " + name
        }

        Controls.Label {
            text: qsTr("MAV ID") + ": " + mavId
        }

        Controls.Label {
            text: qsTr("Mode") + ": " + mode
        }

        Indicators.FlightDirector {
            id: fd
            available: root.online
            armed: root.armed
            pitch: root.ahrs_pitch
            roll: root.ahrs_roll
            speed: root.indicatedAirSpeed
            altitude: root.barometric_altitude
            throttle: root.throttle
            climb: root.barometric_climb
            speedPrefix: qsTr("IAS, m/s")
            altitudePrefix: qsTr("Hbar, m")
            Layout.fillWidth: true
        }

        Indicators.SituationIndicator {
            id: compass
            course: root.satellite_course
            heading: root.compass_heading
            Layout.fillWidth: true
        }
    }

    Controls.Button {
        anchors.top: parent.top
        anchors.right: parent.right
        iconSource: "qrc:/ui/minus.svg"
        onClicked: minimize()
    }
}


