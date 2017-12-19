import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/JS/helper.js" as Helper
import "qrc:/Controls" as Controls
import "qrc:/Indicators" as Indicators

BaseDisplay {
    id: vehicleDisplay

    property alias armed: ai.armed

    property bool ahrsEnabled: false
    property bool ahrsOperational: false
    property alias pitch: ai.pitch
    property alias roll: ai.roll

    property bool satelliteEnabled: false
    property bool satelliteOperational: false
    property real groundspeed: 0
    property int satelliteAltitude: 0

    property bool pitotEnabled: false
    property bool pitotOperational: false
    property real indicatedAirspeed: 0

    property bool barometricEnabled: false
    property bool barometricOperational: false
    property int barometricAltitude: 0

    property bool rangefinderEnabled: false
    property bool rangefinderOperational: false

    property int homeAltitude: 0

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    VehicleDisplayPresenter {
        id: presenter
        view: vehicleDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
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
                Layout.fillWidth: true
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
                prefix: qsTr("TAS")
                suffix: speedUnits ? qsTr("km/h") : qsTr("m/s")
                Layout.fillWidth: true
            }
        }

        Indicators.ArtificialHorizon {
            id: ai
            Layout.fillHeight: true
            implicitWidth: height * 0.75
            enabled: ahrsEnabled
            operational: ahrsOperational
            available: online
            rollInverted: vehicleDisplay.rollInverted
        }

        ColumnLayout {
            Indicators.FdLabel {
                value: satelliteAltitude
                enabled: satelliteEnabled
                operational: satelliteOperational
                prefix: qsTr("SAT")
                suffix: qsTr("m")
                Layout.fillWidth: true
            }

            Indicators.FdLabel {
                value: altitudeRelative ? barometricAltitude - homeAltitude : barometricAltitude
                enabled: barometricEnabled
                operational: barometricOperational
                prefix: qsTr("ALT")
                suffix: qsTr("m")
                Layout.fillWidth: true
            }
        }

        Indicators.Compass {
            Layout.fillHeight: true
            implicitWidth: height
        }
    }
}
