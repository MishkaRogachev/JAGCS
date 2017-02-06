import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/JS/helper.js" as Helper

import "qrc:/Controls"
import "../../Indicators"

ColumnLayout {
    id: root

    property QtObject vehicle

    Item {
        id: sns
        Layout.preferredWidth: root.width
        Layout.preferredHeight: gpsIndicator.height

        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: palette.controlBaseSize / 2

            Label {
                color: fd.snsColor
                font.pixelSize: palette.fontPixelSize * 0.6
                text: qsTr("Lat.:") +
                      (vehicle ? Helper.degreesToDmsString(vehicle.gps.coordinate.latitude,
                                                           false) : qsTr("None"))
            }

            Label {
                color: fd.snsColor
                font.pixelSize: palette.fontPixelSize * 0.6
                text: qsTr("Lon.:") +
                      (vehicle ? Helper.degreesToDmsString(vehicle.gps.coordinate.longitude,
                                                           true) : qsTr("None"))
            }
        }

        Row {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: palette.controlBaseSize / 2
            spacing: 5

            GpsIndicator {
                id: gpsIndicator
                fix: vehicle && vehicle.gpsAvalible ? vehicle.gps.fix : -1
                satellitesVisible: vehicle ? vehicle.gps.satellitesVisible : -1
                anchors.verticalCenter: parent.verticalCenter
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    color: fd.snsColor
                    font.pixelSize: palette.fontPixelSize * 0.6
                    text: qsTr("HDOP:") + (vehicle ? vehicle.gps.eph : qsTr("None"))
                }

                Label {
                    color: fd.snsColor
                    font.pixelSize: palette.fontPixelSize * 0.6
                    text: qsTr("VDOP:") + (vehicle ? vehicle.gps.epv : qsTr("None"))
                }
            }
        }
    }

    FlightDisplay {
        id: fd
        width: palette.controlBaseSize * 8

        insAvalible: vehicle && vehicle.insAvalible
        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        airSpeedAvalible: vehicle && vehicle.airSpeedAvalible
        indicatedAirSpeed: vehicle ? vehicle.indicatedAirSpeed : 0.0
        trueAirSpeed: vehicle ? vehicle.trueAirSpeed : 0.0
        groundSpeed: vehicle ? vehicle.groundSpeed : 0.0
        barometerAvalible: vehicle && vehicle.barometerAvalible
        altitude: vehicle ? vehicle.barometricAltitude : 0.0
        climb: vehicle ? vehicle.barometricClimb : 0.0
        rangeFinderAvalible: vehicle && vehicle.rangeFinderAvalible

        compassAvalible: vehicle && vehicle.compasAvalible
        heading: vehicle ? vehicle.heading : 0.0
        course: vehicle && vehicle.gpsAvalible ? vehicle.gps.course : -1

        snsAltitude: vehicle ? vehicle.gps.coordinate.altitude : 0.0
        snsFix: vehicle && vehicle.gpsAvalible ? vehicle.gps.fix : -1

        rollInverted: parseInt(settings.value("Gui/fdRollInverted"))
    }
/*
    Row {
        anchors.horizontalCenter: parent.horizontalCenter

        BatteryIndicator {
            Layout.alignment: Qt.AlignLeft
            charge: vehicle ? vehicle.powerSystem.charge : -1
        }

        // TODO: delay button
        Button {
            text: vehicle && vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: if (vehicle) vehicle.commandArm(!vehicle.armed)
        }
    }*/
}
