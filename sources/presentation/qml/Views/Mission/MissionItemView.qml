import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls"
import "../Map"

GridLayout {
    id: root

    property int sequence: 0
    property int command: MissionItem.UnknownCommand

    columns: 2

    Label {
        text: qsTr("Item")
        Layout.fillWidth: true
    }

    RowLayout {
        Layout.alignment: Qt.AlignRight

        Button {
            iconSource: "qrc:/icons/left.svg"
        }

        Label {
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredWidth: palette.controlBaseSize
            horizontalAlignment: Qt.AlignHCenter
            text: sequence
        }

        Button {
            iconSource: "qrc:/icons/right.svg"
        }
    }

    Label {
        text: qsTr("Command")
    }

    ComboBox {
        model: [ qsTr("Command") ]
    }

    Label {
        text: qsTr("Altitude")
    }

    SpinBox {

    }

    Label {
        text: qsTr("Altitude relative")
    }

    CheckBox {

    }

    Label {
        text: qsTr("Latitude")
    }

    CoordSpinBox {

    }

    Label {
        text: qsTr("Longitude")
    }

    CoordSpinBox {

    }

    Label {
        text: qsTr("Radius")
    }

    SpinBox {

    }

    Label {
        text: qsTr("Pitch")
    }

    SpinBox {

    }

    Label {
        text: qsTr("Periods")
    }

    SpinBox {

    }

    Item {
        Layout.fillHeight: true
    }
}
