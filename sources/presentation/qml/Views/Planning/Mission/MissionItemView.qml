import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: root

    property bool editEnabled: false
    property bool changed: false
    property int sequence: -1
    property int count: 0
    property int command: MissionItem.UnknownCommand

    property alias commandIndex: commandBox.currentIndex
    property alias commands: commandBox.model

    property int previousAltitude: 0
    property int homeAltitude: 0
    property int abortAltitude: 0
    property alias useAltitudeRelative: altitudeRelativeBox.checked

    property var previousPosition: QtPositioning.coordinate()
    property var position: QtPositioning.coordinate();

    property alias radius: radiusBox.realValue
    property alias repeats: repeatsBox.value
    property alias time: timeBox.realValue
    property alias pitch: pitchBox.realValue
    property alias yaw: yawBox.realValue
    property alias clockwise: clockwiseBox.checked

    property alias isGroundSpeed: isGroundSpeedBar.currentIndex
    property alias speed: speedBox.realValue
    property alias throttle: throttleBox.value
    property alias speedEnabled: speedEnabledBox.checked
    property alias throttleEnabled: throttleEnabledBox.checked

    property bool pitchVisible: command === MissionItem.Takeoff
    property bool abortAltitudeVisible: command === MissionItem.Landing
    property bool altitudeVisible: command === MissionItem.Continue ||
                                   positionVisible

    property bool positionVisible: command === MissionItem.Home ||
                                   azimuthVisible
    property bool distanceVisible: azimuthVisible
    property bool azimuthVisible: command === MissionItem.Takeoff ||
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
    signal updateCommand(int commandIndex)

    onChangedChanged: {
        if (changed) return;

        map.dropPicker()
        pickButton.picking = false;
    }

    onPreviousPositionChanged: updateDistAndAzimuth()
    onPositionChanged: {
        updateAltitude();
        updateClimb();
        updateLatLon();
        updateDistAndAzimuth();
    }
    onPreviousAltitudeChanged: updateClimb()
    onAbortAltitudeChanged: updateAbortAltitude()
    onUseAltitudeRelativeChanged: {
        updateAltitude();
        updateAbortAltitude();
    }
    onHomeAltitudeChanged: {
        if (!useAltitudeRelative) return;

        updateAltitude();
        updateAbortAltitude();
    }

    property bool lockAltitude: false
    function updateAltitude() {
        if (lockAltitude) return;

        lockAltitude = true;
        altitudeBox.realValue = useAltitudeRelative ? position.altitude - homeAltitude : position.altitude;
        lockAltitude = false;
    }

    function updateClimb() {
        climbBox.realValue = position.altitude - previousAltitude;
    }

    function updateAbortAltitude() {
        abortAltitudeBox.realValue = useAltitudeRelative ? abortAltitude - homeAltitude : abortAltitude;
    }

    function updateLatLon() {
        latitudeBox.realValue = position.latitude;
        longitudeBox.realValue = position.longitude;
    }

    property bool lockDistAndAzimuth: false
    function updateDistAndAzimuth() {
        if (!previousPosition.isValid || !position.isValid || lockDistAndAzimuth) return;

        lockDistAndAzimuth = true;
        distanceBox.value = previousPosition.distanceTo(position);
        azimuthBox.realValue = previousPosition.azimuthTo(position);
        lockDistAndAzimuth = false;
    }

    function updateFromDistAndAzimuth() {
        if (lockDistAndAzimuth) return;

        position = previousPosition.atDistanceAndAzimuth(distanceBox.value, azimuthBox.realValue);
    }

    GridLayout {
        anchors.fill: parent
        columns: 2

        Controls.Label {
            text: qsTr("Item")
            Layout.fillWidth: true
            Layout.minimumWidth: palette.controlBaseSize * 3
        }

        RowLayout {
            Controls.Button {
                iconSource: "qrc:/icons/remove.svg"
                iconColor: palette.dangerColor
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
            enabled: editEnabled
            currentIndex: 0
            onCurrentIndexChanged: {
                updateCommand(currentIndex);
                changed = true;
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Altitude")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        GridLayout {
            visible: altitudeVisible
            columns: 2
            Layout.rowSpan: abortAltitudeVisible ? 2 : 1

            Controls.RealSpinBox {
                id: altitudeBox
                enabled: editEnabled
                realFrom: -20000 // 418 m Dead Sea shore
                realTo: 20000 // TODO: constants to config
                onRealValueChanged: {
                    position.altitude = useAltitudeRelative ? realValue + homeAltitude : realValue;
                    updateClimb();
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.CheckBox {
                id: altitudeRelativeBox
                text: qsTr("Rel.")
                enabled: editEnabled && sequence > 0
                onCheckedChanged: changed = true
                Layout.rowSpan: 2
            }

            Controls.RealSpinBox {
                id: abortAltitudeBox
                visible: abortAltitudeVisible
                enabled: editEnabled
                realFrom: -500 // 418 m Daed Sea shore
                realTo: 20000 // TODO: constants to config
                onRealValueChanged: {
                    abortAltitude = useAltitudeRelative ? realValue + homeAltitude : realValue;
                    changed = true;
                }
                Layout.fillWidth: true
            }
        }

        Controls.Label {
            text: qsTr("Abort alt.")
            visible: abortAltitudeVisible
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Climb")
            visible: altitudeVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: climbBox
            visible: altitudeVisible
            realFrom: -20000
            realTo: 20000 // TODO: constants to config
            onRealValueChanged: {
                position.altitude = previousAltitude + realValue;
                updateAltitude();
            }
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Latitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        GridLayout {
            columns: 2
            Layout.rowSpan: 2
            visible: positionVisible

            Controls.CoordSpinBox {
                id: latitudeBox
                enabled: editEnabled
                onRealValueChanged: {
                    position.latitude = realValue;
                    updateDistAndAzimuth();
                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.MapPickButton {
                id: pickButton
                enabled: editEnabled
                Layout.rowSpan: 2
                onPicked: {
                    latitudeBox.realValue = coordinate.latitude;
                    longitudeBox.realValue = coordinate.longitude;
                }
            }

            Controls.CoordSpinBox {
                id: longitudeBox
                enabled: editEnabled
                isLongitude: true
                onRealValueChanged: {
                    position.longitude = realValue;
                    updateDistAndAzimuth();
                    changed = true;
                }
                Layout.fillWidth: true
            }
        }

        Controls.Label {
            text: qsTr("Longitude")
            visible: positionVisible
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Distance")
            visible: distanceVisible
            Layout.fillWidth: true
        }

        Controls.SpinBox {
            id: distanceBox
            visible: distanceVisible
            onValueChanged: updateFromDistAndAzimuth()
            to: 200000 // TODO: constants to config
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Azimuth")
            visible: azimuthVisible
            Layout.fillWidth: true
        }

        Controls.RealSpinBox {
            id: azimuthBox
            visible: azimuthVisible
            onRealValueChanged: updateFromDistAndAzimuth()
            realTo: 360
            Layout.fillWidth: true
        }

        Controls.Label {
            text: qsTr("Radius")
            visible: radiusVisible
            Layout.fillWidth: true
        }

        RowLayout {
            visible: radiusVisible

            Controls.RealSpinBox {
                id: radiusBox
                enabled: editEnabled
                realTo: 5000 // TODO: constants to config
                onRealValueChanged: changed = true
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
            Layout.fillWidth: true
        }

        Controls.CheckBox {
            id: speedEnabledBox
            visible: speedVisible
            enabled: editEnabled
            onCheckedChanged: changed = true
            text: qsTr("Speed")
        }

        Controls.RealSpinBox {
            id: speedBox
            visible: speedVisible
            enabled: editEnabled && speedEnabled
            onRealValueChanged: changed = true
            Layout.fillWidth: true
        }

        Controls.TabBar {
            id: isGroundSpeedBar

            Controls.TabButton {
                text: qsTr("Ground speed")
            }
            Controls.TabButton {
                text: qsTr("Air speed")
            }

            enabled: editEnabled && speedEnabled
            visible: speedVisible
            onCurrentIndexChanged: changed = true
            Layout.fillWidth: true
            Layout.columnSpan: 2
        }

        Controls.CheckBox {
            id: throttleEnabledBox
            visible: speedVisible
            enabled: editEnabled
            onCheckedChanged: changed = true
            text: qsTr("Throttle")
        }

        Controls.SpinBox {
            id: throttleBox
            visible: speedVisible
            enabled: editEnabled && throttleEnabled
            onValueChanged: changed = true
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
            Layout.columnSpan: 2
        }

        RowLayout {
            Layout.columnSpan: 2
            enabled: changed

            Controls.Button {
                text: qsTr("Restore")
                iconSource: "qrc:/icons/restore.svg"
                onClicked: restore()

                Layout.fillWidth: true
            }

            Controls.Button {
                text: qsTr("Save")
                iconSource: "qrc:/icons/save.svg"
                onClicked: save()
                enabled: editEnabled
                Layout.fillWidth: true
            }
        }
    }
}
