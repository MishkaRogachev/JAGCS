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
    property real barometricalAltitude
    property int throttle
    property real barometricClimb

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
            text: qsTr("Mode") + ": " + modeString
        }

        Indicators.FlightDirector {
            id: fd
            available: root.online
            armed: root.armed
            pitch: root.pitch
            roll: root.roll
            speed: root.indicatedAirSpeed
            altitude: root.barometricalAltitude
            throttle: root.throttle
            climb: root.barometricClimb
            speedPrefix: qsTr("IAS, m/s")
            altitudePrefix: qsTr("Hbar, m")
            Layout.fillWidth: true
        }

        Indicators.SituationIndicator {
            id: compass
            course: root.course
            heading: root.heading
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


