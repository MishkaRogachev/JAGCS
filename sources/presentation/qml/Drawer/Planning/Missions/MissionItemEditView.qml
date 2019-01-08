import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

ColumnLayout {
    id: itemEdit

    property bool editEnabled: true
    property bool changed: false
    property int itemId: 0
    property int command: MissionItem.UnknownCommand

    property alias commandIndex: commandBox.currentIndex
    property alias commands: commandBox.model

    property real homeAltitude: 0
    property real previousGlobalAltitude: 0
    property alias altitude: altitudeBox.realValue
    property alias climb: climbBox.realValue
    property alias abortAltitude: abortAltitudeBox.realValue
    property alias altitudeRelative: altitudeRelativeBox.checked

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

    property bool positionVisible: command === MissionItem.Home || azimuthVisible
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

    onItemIdChanged: presenter.setItem(itemId)

    onPositionChanged: {
        updateLatLon();
        updateDistAndAzimuthFromPos();
    }

    onPreviousPositionChanged: updateDistAndAzimuthFromPos()
    onPreviousGlobalAltitudeChanged: updateAltitudeFromClimb()
    onClimbChanged: updateAltitudeFromClimb()
    onAltitudeChanged: updateClimbFromAltitude()
    onAltitudeRelativeChanged: updateClimbFromAltitude()

    // TODO: refactor mission item params view and presenter


    function save() {
        presenter.save();
    }

    function update() {
        presenter.updateItem();
    }

    property bool lockAltitude: false
    function updateAltitudeFromClimb() {
        if (lockAltitude) return;

        lockAltitude = true;
        altitude = previousGlobalAltitude + climb - (altitudeRelative ? homeAltitude : 0)
        lockAltitude = false;
    }

    function updateClimbFromAltitude() {
        if (lockAltitude) return;

        lockAltitude = true;
        climb = (altitudeRelative ? homeAltitude + altitude : altitude) - previousGlobalAltitude;
        lockAltitude = false;
    }

    function updateLatLon() {
        latitudeBox.value = position.latitude;
        longitudeBox.value = position.longitude;
    }

    property bool lockDistAndAzimuth: false
    function updateDistAndAzimuthFromPos() {
        if (!previousPosition.isValid || !position.isValid || lockDistAndAzimuth) return;

        lockDistAndAzimuth = true;
        distanceBox.realValue = previousPosition.distanceTo(position);
        azimuthBox.realValue = previousPosition.azimuthTo(position);
        lockDistAndAzimuth = false;
    }

    function updatePosFromDistAndAzimuth() {
        if (lockDistAndAzimuth) return;

        var newPosition = previousPosition.atDistanceAndAzimuth(distanceBox.realValue,
                                                                azimuthBox.realValue);
        position.latitude = newPosition.latitude;
        position.longitude = newPosition.longitude;
        updateLatLon();
    }

    spacing: industrial.spacing

    MissionItemEditPresenter {
        id: presenter
        view: itemEdit
        Component.onCompleted: setItem(itemId)
    }

    Controls.ComboBox {
        id: commandBox
        labelText: qsTr("Command")
        enabled: editEnabled
        visible: itemId > 0
        currentIndex: 0
        onCurrentIndexChanged: {
            presenter.updateCommand(currentIndex);
            changed = true;
        }
        Layout.fillWidth: true
    }

    Flickable {
        contentHeight: col.height
        clip: true
        Layout.fillWidth: true
        Layout.fillHeight: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        ColumnLayout {
            id: col
            width: parent.width
            spacing: industrial.spacing

            GridLayout {
                rowSpacing: industrial.spacing
                columnSpacing: industrial.spacing
                visible: altitudeVisible
                columns: 2

                Controls.RealSpinBox {
                    id: altitudeBox
                    labelText: qsTr("Altitude")
                    enabled: editEnabled
                    realFrom: settings.value("Parameters/minAltitude")
                    realTo: settings.value("Parameters/maxAltitude")
                    precision: settings.value("Parameters/precisionAltitude")
                    onRealValueChanged: changed = true;
                    Layout.fillWidth: true
                }

                Controls.CheckBox {
                    id: altitudeRelativeBox
                    text: qsTr("Rel.")
                    font.pixelSize: industrial.auxFontSize
                    enabled: editEnabled && command !== MissionItem.Home
                    onCheckedChanged: changed = true
                    Layout.rowSpan: 2
                }

                Controls.RealSpinBox {
                    id: abortAltitudeBox
                    labelText: qsTr("Abort alt.")
                    visible: abortAltitudeVisible
                    enabled: editEnabled
                    realFrom: settings.value("Parameters/minAltitude")
                    realTo: settings.value("Parameters/maxAltitude")
                    precision: settings.value("Parameters/precisionAltitude")
                    onRealValueChanged: changed = true;
                    Layout.fillWidth: true
                }
            }

            Controls.RealSpinBox {
                id: climbBox
                labelText:qsTr("Climb")
                visible: altitudeVisible
                enabled: editEnabled
                realFrom: settings.value("Parameters/minAltitude")
                realTo: settings.value("Parameters/maxAltitude")
                precision: settings.value("Parameters/precisionAltitude")
                Layout.fillWidth: true
            }

            Controls.CoordSpinBox {
                id: latitudeBox
                labelText: qsTr("Latitude")
                enabled: editEnabled
                visible: positionVisible
                onValueChanged: {
                    position.latitude = value;
                    updateDistAndAzimuthFromPos();

                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.CoordSpinBox {
                id: longitudeBox
                labelText: qsTr("Longitude")
                enabled: editEnabled
                visible: positionVisible
                isLongitude: true
                onValueChanged: {
                    position.longitude = value;
                    updateDistAndAzimuthFromPos();

                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.RealSpinBox {
                id: distanceBox
                labelText: qsTr("Distance")
                visible: distanceVisible
                enabled: editEnabled
                onRealValueChanged: updatePosFromDistAndAzimuth()
                realTo: settings.value("Parameters/maxDistance")
                Layout.fillWidth: true
            }

            Controls.RealSpinBox {
                id: azimuthBox
                labelText: qsTr("Azimuth")
                visible: azimuthVisible
                enabled: editEnabled
                onRealValueChanged: updatePosFromDistAndAzimuth()
                realFrom: -180
                realTo: 360
                Layout.fillWidth: true
            }

            RowLayout {
                spacing: industrial.spacing
                visible: radiusVisible

                Controls.RealSpinBox {
                    id: radiusBox
                    labelText: qsTr("Radius")
                    enabled: editEnabled
                    realTo: settings.value("Parameters/maxRadius")
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

            Controls.RealSpinBox {
                id: pitchBox
                labelText: qsTr("Pitch")
                visible: pitchVisible
                enabled: editEnabled
                realFrom: -90
                realTo: 90
                onRealValueChanged: changed = true
                Layout.fillWidth: true
            }

            Controls.RealSpinBox {
                id: yawBox
                labelText: qsTr("Yaw")
                visible: yawVisible
                enabled: editEnabled
                realFrom: -180
                realTo: 360
                onRealValueChanged: changed = true
                Layout.fillWidth: true
            }

            Controls.SpinBox {
                id: repeatsBox
                labelText: qsTr("Repeats")
                visible: repeatsVisible
                onValueChanged: changed = true
                Layout.fillWidth: true
            }

            Controls.RealSpinBox {
                id: timeBox
                labelText: qsTr("Time")
                visible: timeVisible
                enabled: editEnabled
                onRealValueChanged: changed = true
                Layout.fillWidth: true
            }

            RowLayout {
                spacing: industrial.spacing
                visible: speedVisible

                Controls.CheckBox {
                    id: speedEnabledBox
                    enabled: editEnabled
                    onCheckedChanged: changed = true
                }

                Controls.RealSpinBox {
                    id: speedBox
                    labelText: qsTr("Speed")
                    enabled: editEnabled && speedEnabled
                    realFrom: settings.value("Parameters/minSpeed")
                    realTo: settings.value("Parameters/maxSpeed")
                    precision: settings.value("Parameters/precisionSpeed")
                    onRealValueChanged: changed = true
                    Layout.fillWidth: true
                }
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
            }

            RowLayout {
                spacing: industrial.spacing
                visible: speedVisible

                Controls.CheckBox {
                    id: throttleEnabledBox
                    enabled: editEnabled
                    onCheckedChanged: changed = true
                }

                Controls.SpinBox {
                    id: throttleBox
                    labelText: qsTr("Throttle")
                    enabled: editEnabled && throttleEnabled
                    from: 0
                    to: 100
                    onValueChanged: changed = true
                    Layout.fillWidth: true
                }
            }
        }
    }
}

