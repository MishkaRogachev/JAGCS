import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators
import "../CommandControls" as CommandControls

BaseDisplay {
    id: vehicleDisplay

    property alias armed: ah.armed

    property int mode: Domain.None
    property var availableModes: []

    property alias ahrsEnabled: ah.enabled
    property alias ahrsOperational: ah.operational
    property alias pitch: ah.pitch
    property alias roll: ah.roll

//    property bool compassEnabled: compass.enabled
//    property bool compassOperational: compass.operational
//    property alias heading: compass.yaw

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property real groundspeed: 0

    property bool pitotEnabled: false
    property bool pitotOperational: false
    property real indicatedAirspeed: 0

    property bool barometricEnabled: false
    property bool barometricOperational: false
    property int barometricAltitude: 0

    property int homeAltitude: 0

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    GridLayout {
        anchors.fill: parent
        columns: 4

        Indicators.Compass {
            id: compass
            Layout.rowSpan: 3
            Layout.fillHeight: true
            implicitWidth: height
            tickFactor: 15
            scalesRatio: 0.08
            minorTickOffset: 0.2 * scalesOffset
            majorTickOffset: 0.4 * scalesOffset

            Indicators.ArtificialHorizon {
                id: ah
                anchors.centerIn: parent
                height: parent.height -(compass.textOffset + compass.majorTickOffset) * 2
                width: height// * 0.75
                available: online
            }
        }

        Indicators.FdLabel {
            digits: 0
            value: {
                switch (speedUnits) {
                default:
                case 0: return groundspeed;
                case 1: return Helper.mpsToKph(groundspeed);
                }
            }
            enabled: satelliteEnabled
            operational: satelliteOperational
            prefix: qsTr("GS")
            suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
            Layout.preferredWidth: parent.width * 0.2
        }

        Controls.Label {
            text: vehicleName
            Layout.fillWidth: true
        }

        Controls.Button {
            flat: true
            iconSource: "qrc:/icons/right.svg"
            onClicked: dashboard.selectVehicle(vehicleId, vehicleName)
        }

        Indicators.FdLabel {
            digits: 0
            value: {
                switch (speedUnits) {
                default:
                case 0: return indicatedAirspeed;
                case 1: return Helper.mpsToKph(indicatedAirspeed);
                }
            }
            enabled: pitotEnabled
            operational: pitotOperational
            prefix: qsTr("IAS")
            suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
            Layout.preferredWidth: parent.width * 0.2
        }

        CommandControls.ModeBox {
            id: modeBox
            mode: vehicleDisplay.mode
            model: availableModes
            tipText: qsTr("Select mode")
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Indicators.FdLabel {
            value: altitudeRelative ? barometricAltitude - homeAltitude : barometricAltitude
            enabled: barometricEnabled
            operational: barometricOperational
            prefix: qsTr("ALT")
            suffix: qsTr("m")
            Layout.preferredWidth: parent.width * 0.2
        }

        // TODO: select mission item
    }
}
