import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/JS/helper.js" as Helper

import "qrc:/Controls"
import "../../Indicators"

ColumnLayout {
    id: root

    property QtObject vehicle

    spacing: 0

    Item {
        id: sns
        Layout.preferredWidth: root.width
        Layout.preferredHeight: gpsColumn.height + palette.controlBaseSize / 4

        Column {
            id: gpsColumn
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: palette.controlBaseSize / 8

            Label {
                color: fd.snsColor
                font.pixelSize: palette.fontPixelSize * 0.6
                font.bold: true
                text: qsTr("Lat.:") +
                      (vehicle ? Helper.degreesToDmsString(vehicle.gps.coordinate.latitude,
                                                           false) : qsTr("None"))
            }

            Label {
                color: fd.snsColor
                font.pixelSize: palette.fontPixelSize * 0.6
                font.bold: true
                text: qsTr("Lon.:") +
                      (vehicle ? Helper.degreesToDmsString(vehicle.gps.coordinate.longitude,
                                                           true) : qsTr("None"))
            }
        }

        Row {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: palette.controlBaseSize / 8
            spacing: 5

            GpsIndicator {
                fix: vehicle && vehicle.gpsAvalible ? vehicle.gps.fix : -1
                satellitesVisible: vehicle ? vehicle.gps.satellitesVisible : -1
                anchors.verticalCenter: parent.verticalCenter
                width: palette.controlBaseSize
                height: width
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    color: fd.snsColor
                    font.pixelSize: palette.fontPixelSize * 0.6
                    font.bold: true
                    text: qsTr("HDOP:") + (vehicle ? vehicle.gps.eph : qsTr("None"))
                }

                Label {
                    color: fd.snsColor
                    font.pixelSize: palette.fontPixelSize * 0.6
                    font.bold: true
                    text: qsTr("VDOP:") + (vehicle ? vehicle.gps.epv : qsTr("None"))
                }
            }
        }
    }

    FlightDisplay {
        id: fd
        width: palette.controlBaseSize * 8

        armed: vehicle && vehicle.armed
        insAvalible: vehicle && vehicle.insAvalible
        pitch: vehicle ? vehicle.attitude.pitch : 0.0
        roll: vehicle ? vehicle.attitude.roll : 0.0
        airSpeedAvalible: vehicle && vehicle.airSpeedAvalible
        indicatedAirSpeed: vehicle ? vehicle.indicatedAirSpeed : 0.0
        trueAirSpeed: vehicle ? vehicle.trueAirSpeed : 0.0
        windSpeed: vehicle ? vehicle.wind.speed: 0.0
        groundSpeed: vehicle ? vehicle.groundSpeed : 0.0
        barometerAvalible: vehicle && vehicle.barometerAvalible
        altitude: vehicle ? vehicle.barometricAltitude : 0.0
        climb: vehicle ? vehicle.barometricClimb : 0.0
        throttle: vehicle ? vehicle.throttle : 0
        rangeFinderAvalible: vehicle && vehicle.rangeFinderAvalible

        compassAvalible: vehicle && vehicle.compasAvalible
        heading: vehicle ? vehicle.heading : 0.0
        course: vehicle && vehicle.gpsAvalible ? vehicle.gps.course : -1
        windDirection: vehicle ? vehicle.wind.direction : -1
        homeDirection: vehicle ? vehicle.homeDirection : -1
        homeDistance: vehicle ? vehicle.homeDistance : -1
        missionDistance: vehicle ? vehicle.missionDistance : -1

        snsAltitude: vehicle ? vehicle.gps.altitude : 0.0
        snsFix: vehicle && vehicle.gpsAvalible ? vehicle.gps.fix : -1

        charge: vehicle ? vehicle.powerSystem.charge : -1
        voltage: vehicle ? vehicle.powerSystem.voltage : -1
        current: vehicle ? vehicle.powerSystem.current : -1

        rollInverted: parseInt(settings.value("Gui/fdRollInverted"))
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            horizontalAlignment: Qt.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Mode:") + ' ' + (vehicle ? vehicle.modeString : "-")
            font.bold: true
            Layout.preferredWidth: fd.width * 2 / 3
        }

        Switch {
            anchors.verticalCenter: parent.verticalCenter
            text: inputChecked ? qsTr("Disarm") : qsTr("Arm")
            font.pixelSize: palette.fontPixelSize / 1.5
            font.bold: true
            Layout.preferredWidth: fd.width / 3
            inputChecked: vehicle && vehicle.armed
            onInputCheckedChanged: checked = inputChecked
            onCheckedChanged: if (checked != inputChecked) vehicle.commandArmDisarm(checked)
            enabled: vehicle
        }
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter

        Label {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("Item")
            font.bold: true
        }

        ComboBox {
            id: selectedItemBox
            anchors.verticalCenter: parent.verticalCenter
            model: vehicle ? vehicle.missionItems : []
            enabled: vehicle
        }

        Button {
            iconSource: "qrc:/icons/play.svg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: vehicle.commandJumpTo(selectedItemBox.currentText)
            enabled: vehicle
        }

        Button {
            iconSource: "qrc:/icons/home.svg"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: vehicle.commandReturn()
            enabled: vehicle
        }
    }
}
