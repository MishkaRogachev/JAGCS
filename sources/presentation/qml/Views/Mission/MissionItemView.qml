import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"
import "../Map"

GridLayout {
    id: root

    property int sequence: -1
    property int count: 0

    property int command: MissionItem.UnknownCommand

    property bool altitudeVisible: command == MissionItem.Continue ||
                                   positionVisible

    property bool positionVisible: command == MissionItem.Takeoff ||
                                   command == MissionItem.Waypoint ||
                                   command == MissionItem.Landing ||
                                   radiusVisible

    property bool radiusVisible: command == MissionItem.LoiterAltitude ||
                                 command == MissionItem.LoiterTurns

    property bool pitchVisible: command == MissionItem.Takeoff
    property bool periodsVisible: command == MissionItem.periods

    signal selectItem(int sequence)
    signal addItem()
    signal removeItem()

    signal setCommand(int command);

    columns: 2

    RowLayout {
        Layout.columnSpan: 2

        Label {
            text: qsTr("Item")
            Layout.fillWidth: true
        }

        Button {
            iconSource: "qrc:/icons/remove.svg"
            enabled: sequence >= 0
            onClicked: removeItem()
        }

        Button {
            iconSource: "qrc:/icons/left.svg"
            enabled: sequence != -1 && sequence > 0
            onClicked: selectItem(sequence - 1)
        }

        Label {
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredWidth: palette.controlBaseSize
            horizontalAlignment: Qt.AlignHCenter
            text: sequence > -1 ? sequence : "-"
        }

        Button {
            iconSource: "qrc:/icons/right.svg"
            enabled: sequence != -1 && sequence + 1 < count
            onClicked: selectItem(sequence + 1)
        }

        Button {
            iconSource: "qrc:/icons/add.svg"
            enabled: sequence != -1 && sequence + 1 == count
            onClicked: addItem()
        }
    }

    Label {
        text: qsTr("Command")
        visible: sequence !== -1
    }

    ComboBox {
        model: [ qsTr("Takeoff"), qsTr("Waypoint"),
            qsTr("LoiterAltitude"), qsTr("LoiterTurns"), qsTr("Continue"),
            qsTr("Return"), qsTr("Landing") ]
        visible: sequence !== -1
    }

    Label {
        text: qsTr("Altitude")
        visible: altitudeVisible
    }

    SpinBox {
        visible: altitudeVisible
    }

    Label {
        text: qsTr("Altitude relative")
        visible: altitudeVisible
    }

    CheckBox {
        visible: altitudeVisible
    }

    Label {
        text: qsTr("Latitude")
        visible: positionVisible
    }

    CoordSpinBox {
        visible: positionVisible
    }

    Label {
        text: qsTr("Longitude")
        visible: positionVisible
    }

    CoordSpinBox {
        visible: positionVisible
    }

    Label {
        text: qsTr("Radius")
        visible: radiusVisible
    }

    SpinBox {
        visible: radiusVisible
    }

    Label {
        text: qsTr("Pitch")
        visible: pitchVisible
    }

    SpinBox {
        visible: pitchVisible
    }

    Label {
        text: qsTr("Periods")
        visible: periodsVisible
    }

    SpinBox {
        visible: periodsVisible
    }

    Item {
        Layout.fillHeight: true
    }
}
