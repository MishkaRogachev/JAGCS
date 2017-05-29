import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtCharts 2.0
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

AbstractVehicleView {
    id: root

    signal maximize()

    RowLayout {

        Indicators.ArtificialHorizon {
            available: root.online
            armed: root.armed
            pitch: root.pitch
            roll: root.roll
            pitchScaleEnabled: false
            markWidth: 2
            Layout.minimumWidth: palette.controlBaseSize * 2
        }

        Indicators.Compass {
            id: compass
            tickFactor: 15
            scalesRatio: 0.11
            course: root.course
            heading: root.heading
            Layout.minimumWidth: palette.controlBaseSize * 3
        }

        GridLayout {
            columns: 2

            Controls.Label {
                text: qsTr("MAV ID") + ": " + mavId
                Layout.fillWidth: true
            }

            Controls.Button {
                iconSource: "qrc:/ui/plus.svg"
                onClicked: maximize()
                Layout.alignment: Qt.AlignRight
            }

            Controls.Label {
                text: qsTr("MAV") + ": " + name
                Layout.columnSpan: 2
            }

            Controls.Label {
                text: qsTr("Mode") + ": " + modeString
                Layout.columnSpan: 2
            }
        }
    }
}

