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

        SpinBox {
            visible: altitudeVisible
        }

        Label {
            text: qsTr("Altitude relative")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        CheckBox {
            visible: altitudeVisible
        }

        Label {
            text: qsTr("Latitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        CoordSpinBox {
            visible: positionVisible
        }

        Label {
            text: qsTr("Longitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        CoordSpinBox {
            visible: positionVisible
        }

        Label {
            text: qsTr("Radius")
            visible: radiusVisible
            Layout.fillWidth: true
        }

        SpinBox {
            visible: radiusVisible
        }

        Label {
            text: qsTr("Pitch")
            visible: pitchVisible
            Layout.fillWidth: true
        }

        SpinBox {
            visible: pitchVisible
        }

        Label {
            text: qsTr("Periods")
            visible: periodsVisible
            Layout.fillWidth: true
        }

        SpinBox {
            visible: periodsVisible
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
