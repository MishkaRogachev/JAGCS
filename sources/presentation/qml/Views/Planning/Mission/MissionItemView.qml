import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property bool changed: false
    property int sequence: -1
    property int count: 0

    property alias command: commandBox.currentIndex
    property alias commands: commandBox.model

    property alias altitude: altitudeEdit.realValue
    property alias isAltitudeRelative: altitudeRelativeEdit.checked
    property alias latitude: latitudeEdit.realValue
    property alias longitude: longitudeEdit.realValue
    property alias radius: radiusEdit.realValue
    property alias periods: periodsEdit.value
    property alias delay: delayEdit.realValue
    property alias pitch: pitchEdit.realValue

    property bool altitudeVisible: command === MissionItem.Continue ||
                                   positionVisible

    property bool positionVisible: command === MissionItem.Home ||
                                   command === MissionItem.Takeoff ||
                                   command === MissionItem.Landing ||
                                   radiusVisible

    property bool radiusVisible: command === MissionItem.Waypoint ||
                                 command === MissionItem.LoiterUnlim ||
                                 command === MissionItem.LoiterAltitude ||
                                 command === MissionItem.LoiterTurns ||
                                 command === MissionItem.LoiterTime

    property bool delayVisible: command === MissionItem.LoiterTime

    property bool pitchVisible: command === MissionItem.Takeoff
    property bool periodsVisible: command === MissionItem.LoiterTurns

    property alias picking: pickButton.picking

    signal save()
    signal restore()
    signal remove()
    signal selectItem(int sequence)

    onChangedChanged: if (!changed) map.dropPicker()

    GridLayout {
        columns: 3

        Controls.Label {
            text: qsTr("Item")
            Layout.fillWidth: true
        }

        RowLayout {
            Layout.columnSpan: 2

            Controls.Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.negativeColor
                enabled: sequence > -1
                onClicked: remove()
            }

            Controls.Button {
                iconSource: "qrc:/icons/left.svg"
                enabled: sequence > 0
                onClicked: selectItem(sequence - 1)
            }

            Controls.Label {
                Layout.alignment: Qt.AlignVCenter
                Layout.fillWidth: true
                horizontalAlignment: Qt.AlignHCenter
                text: (sequence + 1) + "/" + count
            }

            Controls.Button {
                iconSource: "qrc:/icons/right.svg"
                enabled: sequence + 1 < count
                onClicked: selectItem(sequence + 1)
            }

            Controls.Button {
                iconSource: "qrc:/icons/add.svg"
                enabled: /*sequence == count - 1 &&*/ selectedMission > 0
                onClicked: addItem()
            }
        }

        Controls.Label {
            text: qsTr("Command")
            visible: sequence > -1
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: commandBox
            visible: sequence > -1
            enabled: sequence > 0
            currentIndex: MissionItem.UnknownCommand
            onCurrentIndexChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: sequence > -1 }

        Controls.Label {
            text: qsTr("Altitude")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: altitudeEdit
            visible: altitudeVisible
            realFrom: -500 // 418 m Daed Sea shore
            realTo: 20000 // TODO: constants to config
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: altitudeVisible }

        Controls.Label {
            text: qsTr("Rel. altitude")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: altitudeRelativeEdit
            visible: altitudeVisible
            enabled: sequence > 0
            onCheckedChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: altitudeVisible }

        Controls.Label {
            text: qsTr("Latitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        Controls.CoordSpinBox {
            id: latitudeEdit
            visible: positionVisible
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.MapPickButton {
            id: pickButton
            visible: positionVisible
            Layout.rowSpan: 2
            onPicked: {
                latitudeEdit.realValue = coordinate.latitude;
                longitudeEdit.realValue = coordinate.longitude;
            }
        }

        Controls.Label {
            text: qsTr("Longitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        Controls.CoordSpinBox {
            id: longitudeEdit
            visible: positionVisible
            isLongitude: true
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Label {
            text: qsTr("Radius")
            visible: radiusVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: radiusEdit
            visible: radiusVisible
            realTo: 5000 // TODO: constants to config
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: radiusVisible }

        Controls.Label {
            text: qsTr("Pitch")
            visible: pitchVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: pitchEdit
            visible: pitchVisible
            realFrom: -90
            realTo: 90 // TODO: constants to config
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: pitchVisible }

        Controls.Label {
            text: qsTr("Periods")
            visible: periodsVisible
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
        }

        Controls.SpinBox {
            id: periodsEdit
            visible: periodsVisible
            onValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Label {
            text: qsTr("Delay")
            visible: delayVisible
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
        }

        Controls.RealSpinBox {
            id: delayEdit
            visible: delayVisible
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: periodsVisible }

        Controls.Spacer {
            Layout.fillHeight: true
            Layout.columnSpan: 3
        }

        Controls.Button {
            text: qsTr("Restore")
            iconSource: "qrc:/icons/restore.svg"
            onClicked: restore()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Button {
            text: qsTr("Save")
            iconSource: "qrc:/icons/save.svg"
            onClicked: save()
            enabled: changed
            Layout.fillWidth: true
        }

        Controls.Spacer {}
    }
}
