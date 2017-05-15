import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"
import "../Map"

ColumnLayout {
    id: root

    property int sequence: 0
    property int count: 0

    property int command: MissionItem.UnknownCommand
    property alias commands: commandBox.model

    property alias altitude: altitudeEdit.realValue
    property alias isAltitudeRelative: altitudeRelativeEdit.checked
    property alias latitude: latitudeEdit.realValue
    property alias longitude: longitudeEdit.realValue
    property alias radius: radiusEdit.realValue
    property alias periods: periodsEdit.value
    property alias pitch: pitchEdit.realValue

    property bool altitudeVisible: command == MissionItem.Continue ||
                                   command == MissionItem.Takeoff ||
                                   positionVisible

    property bool positionVisible: command == MissionItem.Landing ||
                                   radiusVisible

    property bool radiusVisible: command == MissionItem.Waypoint ||
                                 command == MissionItem.LoiterAltitude ||
                                 command == MissionItem.LoiterTurns

    property bool pitchVisible: command == MissionItem.Takeoff
    property bool periodsVisible: command == MissionItem.LoiterTurns

    property alias picking: pickButton.checked

    signal selectItem(int sequence)
    signal addItem()
    signal removeItem()

    signal setCommand(int command);
    signal setAltitude(real altitude)
    signal setAltitudeRelative(bool relative)
    signal setLatitude(real latitude)
    signal setLongitude(real longitude)
    signal setRadius(real radius)
    signal setPeriods(int periods)
    signal setPitch(real pitch)

    onCommandChanged: commandBox.currentIndex = command;

    GridLayout {
        columns: 3

        Label {
            text: qsTr("Item")
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.columnSpan: 2

            Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
                enabled: sequence > 0
                onClicked: removeItem()
            }

            Button {
                iconSource: "qrc:/icons/left.svg"
                enabled: sequence > 1
                onClicked: selectItem(sequence - 1)
            }

            Label {
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
                text: sequence + "/" + count
            }

            Button {
                iconSource: "qrc:/icons/right.svg"
                enabled: sequence < count
                onClicked: selectItem(sequence + 1)
            }

            Button {
                iconSource: "qrc:/icons/add.svg"
                enabled: sequence == count && selectedMission > 0
                onClicked: addItem()
            }
        }

        Label {
            text: qsTr("Command")
            visible: sequence !== 0
            Layout.fillWidth: true
        }

        ComboBox {
            id: commandBox
            visible: sequence !== 0
            onCurrentIndexChanged: setCommand(currentIndex)
            Layout.alignment: Qt.AlignRight
        }

        Spacer { visible: sequence !== 0; }

        Label {
            text: qsTr("Altitude")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        RealSpinBox {
            id: altitudeEdit
            visible: altitudeVisible
            realFrom: -500 // 418 m Daed Sea shore
            realTo: 20000 // TODO: constants to config
            onRealValueChanged: setAltitude(realValue)
            Layout.alignment: Qt.AlignRight
        }

        Spacer { visible: altitudeVisible }

        Label {
            text: qsTr("Altitude relative")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        CheckBox {
            id: altitudeRelativeEdit
            visible: altitudeVisible
            onCheckedChanged: setAltitudeRelative(checked)
            Layout.alignment: Qt.AlignRight
        }

        Spacer { visible: altitudeVisible }

        Label {
            text: qsTr("Latitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        CoordSpinBox {
            id: latitudeEdit
            visible: positionVisible
            onRealValueChanged: setLatitude(realValue)
            Layout.alignment: Qt.AlignRight
        }

        MapPickButton {
            id: pickButton
            visible: positionVisible
            Layout.rowSpan: 2
            onPicked: {
                latitudeEdit.realValue = coordinate.latitude;
                longitudeEdit.realValue = coordinate.longitude;
            }
        }

        Label {
            text: qsTr("Longitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        CoordSpinBox {
            id: longitudeEdit
            visible: positionVisible
            isLongitude: true
            onRealValueChanged: setLongitude(realValue)
            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Radius")
            visible: radiusVisible
            Layout.fillWidth: true
        }

        RealSpinBox {
            id: radiusEdit
            visible: radiusVisible
            realTo: 5000 // TODO: constants to config
            onRealValueChanged: setRadius(realValue)
            Layout.alignment: Qt.AlignRight
        }

        Spacer { visible: radiusVisible }

        Label {
            text: qsTr("Pitch")
            visible: pitchVisible
            Layout.fillWidth: true
        }

        RealSpinBox {
            id: pitchEdit
            visible: pitchVisible
            realFrom: -90
            realTo: 90 // TODO: constants to config
            onRealValueChanged: setPitch(realValue)
            Layout.alignment: Qt.AlignRight
        }

        Spacer { visible: pitchVisible }

        Label {
            text: qsTr("Periods")
            visible: periodsVisible
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
        }

        SpinBox {
            id: periodsEdit
            visible: periodsVisible
            onValueChanged: setPeriods(value)
            Layout.alignment: Qt.AlignRight
        }

        Spacer { visible: periodsVisible }

        Spacer {
            Layout.fillHeight: true
        }
    }
}
