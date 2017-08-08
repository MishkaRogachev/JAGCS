import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: root

    property bool editEnabled: false
    property bool changed: false
    property int sequence: -1
    property int count: 0

    property alias command: commandBox.currentIndex
    property alias commands: commandBox.model

    property alias altitude: altitudeBox.realValue
    property alias abortAltitude: abortAltitudeBox.realValue
    property alias isAltitudeRelative: altitudeRelativeBox.checked
    property alias latitude: latitudeBox.realValue
    property alias longitude: longitudeBox.realValue
    property alias radius: radiusBox.realValue
    property alias repeats: repeatsBox.value
    property alias time: timeBox.realValue
    property alias pitch: pitchBox.realValue
    property alias yaw: yawBox.realValue
    property alias clockwise: clockwiseBox.checked

    property alias isGroundSpeed: isGroundSpeedBox.currentIndex
    property alias speed: speedBox.realValue
    property alias throttle: throttleBox.value
    property alias speedEnabled: speedEnabledBox.checked
    property alias throttleEnabled: throttleEnabledBox.checked

    property bool pitchVisible: command === MissionItem.Takeoff
    property bool abortAltitudeVisible: command === MissionItem.Landing
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
    property bool speedVisible: command === MissionItem.SetSpeed

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
        anchors.fill: parent
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
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

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
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: altitudeRelativeBox
            text: qsTr("Rel.")
            visible: altitudeVisible
            enabled: editEnabled && sequence > 0
            onCheckedChanged: changed = true
        }

        Controls.Label {
            text: qsTr("Abort alt.")
            visible: abortAltitudeVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: abortAltitudeBox
            visible: abortAltitudeVisible
            enabled: editEnabled
            realFrom: -500 // 418 m Daed Sea shore
            realTo: 20000 // TODO: constants to config
            onRealValueChanged: changed = true
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

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
            Layout.fillWidth: true
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
            Layout.fillWidth: true
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
            Layout.columnSpan: clockwiseVisible ? 1 : 2
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: clockwiseBox
            text: qsTr("CW")
            visible: clockwiseVisible
            enabled: editEnabled
            onCheckedChanged: changed = true
            Layout.alignment: Qt.AlignRight
        }

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
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

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
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Repeats")
            visible: repeatsVisible
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: repeatsBox
            visible: repeatsVisible
            onValueChanged: changed = true
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Time")
            visible: timeVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: timeBox
            visible: timeVisible
            enabled: editEnabled
            onRealValueChanged: changed = true
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Controls.ComboBox {
            id: isGroundSpeedBox
            model: [ qsTr("Ground speed"), qsTr("Air speed") ]
            enabled: editEnabled && speedEnabled
            visible: speedVisible
            onCurrentIndexChanged: changed = true
        }

        Controls.RealSpinBox {
            id: speedBox
            visible: speedVisible
            enabled: editEnabled && speedEnabled
            onRealValueChanged: changed = true
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: speedEnabledBox
            visible: speedVisible
            enabled: editEnabled
            onCheckedChanged: changed = true
        }

        Controls.Label {
            text: qsTr("Throttle")
            visible: speedVisible
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: throttleBox
            visible: speedVisible
            enabled: editEnabled && throttleEnabled
            onValueChanged: changed = true
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: throttleEnabledBox
            visible: speedVisible
            enabled: editEnabled
            onCheckedChanged: changed = true
        }

        Item {
            Layout.fillHeight: true
            Layout.columnSpan: 3
        }

        RowLayout {
            Layout.columnSpan: 3

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
        }
    }
}
