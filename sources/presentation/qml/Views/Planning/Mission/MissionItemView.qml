import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property bool editEnabled: false
    property bool changed: false
    property int sequence: -1
    property int count: 0

    property alias command: commandBox.currentIndex
    property alias commands: commandBox.model

    property alias altitude: altitudeBox.realValue
    property alias isAltitudeRelative: altitudeRelativeBox.checked
    property alias latitude: latitudeBox.realValue
    property alias longitude: longitudeBox.realValue
    property alias radius: radiusBox.realValue
    property alias repeats: repeatsBox.value
    property alias time: timeBox.realValue
    property alias pitch: pitchBox.realValue
    property alias yaw: yawBox.realValue
    property alias clockwise: clockwiseBox.checked

    property bool pitchVisible: command === MissionItem.Takeoff
    property bool altitudeVisible: command === MissionItem.Continue || positionVisible

    property bool positionVisible: command === MissionItem.Home ||
                                   command === MissionItem.Takeoff ||
                                   command === MissionItem.Landing ||
                                   radiusVisible

    property bool radiusVisible: command === MissionItem.Waypoint || clockwiseVisible

    property bool timeVisible: command === MissionItem.LoiterTime
    property bool clockwiseVisible: yawVisible || command === MissionItem.LoiterAltitude
    property bool yawVisible: command === MissionItem.LoiterUnlim ||
                              command === MissionItem.LoiterTurns ||
                              command === MissionItem.LoiterTime

    property bool repeatsVisible: command === MissionItem.LoiterTurns

    property alias picking: pickButton.picking

    signal save()
    signal restore()
    signal remove()
    signal selectItem(int sequence)

    onChangedChanged: {
        if (changed) return;

        map.dropPicker()
        pickButton.picking = false;
    }

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
                enabled: sequence > -1 && editEnabled
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
                enabled: selectedMission > 0
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
            enabled: editEnabled && sequence > 0
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
            id: altitudeBox
            visible: altitudeVisible
            enabled: editEnabled
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
            id: altitudeRelativeBox
            visible: altitudeVisible
            enabled: editEnabled && sequence > 0
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
            id: latitudeBox
            visible: positionVisible
            enabled: editEnabled
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.MapPickButton {
            id: pickButton
            visible: positionVisible
            enabled: editEnabled
            Layout.rowSpan: 2
            onPicked: {
                latitudeBox.realValue = coordinate.latitude;
                longitudeBox.realValue = coordinate.longitude;
            }
        }

        Controls.Label {
            text: qsTr("Longitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        Controls.CoordSpinBox {
            id: longitudeBox
            visible: positionVisible
            enabled: editEnabled
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
            id: radiusBox
            visible: radiusVisible
            enabled: editEnabled
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
            id: pitchBox
            visible: pitchVisible
            enabled: editEnabled
            realFrom: -90
            realTo: 90 // TODO: constants to config
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: pitchVisible }

        Controls.Label {
            text: qsTr("Yaw")
            visible: yawVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: yawBox
            visible: yawVisible
            enabled: editEnabled
            realFrom: -180
            realTo: 360 // TODO: constants to config
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: yawVisible }

        Controls.Label {
            text: qsTr("Clockwise")
            visible: clockwiseVisible
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: clockwiseBox
            visible: clockwiseVisible
            enabled: editEnabled
            onCheckedChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: clockwiseVisible }

        Controls.Label {
            text: qsTr("Repeats")
            visible: repeatsVisible
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
        }

        Controls.SpinBox {
            id: repeatsBox
            visible: repeatsVisible
            onValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Label {
            text: qsTr("Time")
            visible: timeVisible
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
        }

        Controls.RealSpinBox {
            id: timeBox
            visible: timeVisible
            enabled: editEnabled
            onRealValueChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

        Controls.Spacer { visible: repeatsVisible }

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
            enabled: editEnabled && changed
            Layout.fillWidth: true
        }

        Controls.Spacer {}
    }
}
