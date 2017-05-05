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
                                   positionVisible

    property bool positionVisible: command == MissionItem.Takeoff ||
                                   command == MissionItem.Waypoint ||
                                   command == MissionItem.Landing ||
                                   radiusVisible

    property bool radiusVisible: command == MissionItem.LoiterAltitude ||
                                 command == MissionItem.LoiterTurns

    property bool pitchVisible: command == MissionItem.Takeoff
    property bool periodsVisible: command == MissionItem.LoiterTurns

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

    RowLayout {
        Layout.columnSpan: 2

        Label {
            text: qsTr("Item")
            Layout.fillWidth: true
        }

        Button {
            iconSource: "qrc:/icons/remove.svg"
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
            Layout.preferredWidth: palette.controlBaseSize
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
            enabled: sequence == count && selectedMission.length > 0
            onClicked: addItem()
        }
    }

    GridLayout {
        columns: 2

        Label {
            text: qsTr("Command")
            visible: sequence !== 0
            Layout.fillWidth: true
        }

        ComboBox {
            id: commandBox
            visible: sequence !== 0
            onCurrentIndexChanged: setCommand(currentIndex)
        }

        Label {
            text: qsTr("Altitude")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        RealSpinBox {
            id: altitudeEdit
            visible: altitudeVisible
            onRealValueChanged: setAltitude(realValue)
        }

        Label {
            text: qsTr("Altitude relative")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        CheckBox {
            id: altitudeRelativeEdit
            visible: altitudeVisible
            onCheckedChanged: setAltitudeRelative(checked)
        }

        Label {
            text: qsTr("Latitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        CoordSpinBox {
            id: latitudeEdit
            visible: positionVisible
            onRealValueChanged: setLatitude(realValue)
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
        }

        Label {
            text: qsTr("Radius")
            visible: radiusVisible
            Layout.fillWidth: true
        }

        RealSpinBox {
            id: radiusEdit
            visible: radiusVisible
            onRealValueChanged: setRadius(realValue)
            to: 300000
        }

        Label {
            text: qsTr("Pitch")
            visible: pitchVisible
            Layout.fillWidth: true
        }

        RealSpinBox {
            id: pitchEdit
            visible: pitchVisible
            onRealValueChanged: setPitch(realValue)
        }

        Label {
            text: qsTr("Periods")
            visible: periodsVisible
            Layout.fillWidth: true
        }

        SpinBox {
            id: periodsEdit
            visible: periodsVisible
            onValueChanged: setPeriods(value)
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
