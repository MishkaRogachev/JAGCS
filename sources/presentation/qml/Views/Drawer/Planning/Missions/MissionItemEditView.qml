import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "qrc:/Views/Common"

Item {
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

    MissionItemEditPresenter {
        id: presenter
        view: itemEdit
        Component.onCompleted: setItem(itemId)
    }

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: saveRestore.height
        contentHeight: grid.height
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        GridLayout {
            id: grid
            width: parent.width
            rowSpacing: sizings.spacing
            columnSpacing: sizings.spacing
            columns: 2

            Controls.Label {
                text: qsTr("Command")
                Layout.fillWidth: true
            }

            Controls.ComboBox {
                id: commandBox
                enabled: editEnabled
                currentIndex: 0
                onCurrentIndexChanged: {
                    presenter.updateCommand(currentIndex);
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
                rowSpacing: sizings.spacing
                columnSpacing: sizings.spacing
                visible: altitudeVisible
                columns: 2
                Layout.rowSpan: abortAltitudeVisible ? 2 : 1

                Controls.RealSpinBox {
                    id: altitudeBox
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
                    enabled: editEnabled && command !== MissionItem.Home
                    onCheckedChanged: changed = true
                    Layout.rowSpan: 2
                }

                Controls.RealSpinBox {
                    id: abortAltitudeBox
                    visible: abortAltitudeVisible
                    enabled: editEnabled
                    realFrom: settings.value("Parameters/minAltitude")
                    realTo: settings.value("Parameters/maxAltitude")
                    precision: settings.value("Parameters/precisionAltitude")
                    onRealValueChanged: changed = true;
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
                enabled: editEnabled
                realFrom: settings.value("Parameters/minAltitude")
                realTo: settings.value("Parameters/maxAltitude")
                precision: settings.value("Parameters/precisionAltitude")
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Latitude")
                visible: positionVisible
                Layout.fillWidth: true
            }

            Controls.CoordSpinBox {
                id: latitudeBox
                enabled: editEnabled
                visible: positionVisible
                onValueChanged: {
                    position.latitude = value;
                    updateDistAndAzimuthFromPos();

                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Longitude")
                visible: positionVisible
                Layout.fillWidth: true
            }

            Controls.CoordSpinBox {
                id: longitudeBox
                enabled: editEnabled
                isLongitude: true
                onValueChanged: {
                    position.longitude = value;
                    updateDistAndAzimuthFromPos();

                    changed = true;
                }
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Distance")
                visible: distanceVisible
                Layout.fillWidth: true
            }

            Controls.RealSpinBox {
                id: distanceBox
                visible: distanceVisible
                enabled: editEnabled
                onRealValueChanged: updatePosFromDistAndAzimuth()
                realTo: settings.value("Parameters/maxDistance")
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
                enabled: editEnabled
                onRealValueChanged: updatePosFromDistAndAzimuth()
                realFrom: -180
                realTo: 360
                Layout.fillWidth: true
            }

            Controls.Label {
                text: qsTr("Radius")
                visible: radiusVisible
                Layout.fillWidth: true
            }

            RowLayout {
                spacing: sizings.spacing
                visible: radiusVisible

                Controls.RealSpinBox {
                    id: radiusBox
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
                realTo: 90
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
                realTo: 360
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
                realFrom: settings.value("Parameters/minSpeed")
                realTo: settings.value("Parameters/maxSpeed")
                precision: settings.value("Parameters/precisionSpeed")
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
                from: 0
                to: 100
                onValueChanged: changed = true
                Layout.fillWidth: true
            }
        }
    }

    SaveRestore {
        id: saveRestore
        width: parent.width
        anchors.bottom: parent.bottom
        enabled: changed && editEnabled
        onSave: presenter.save()
        onRestore: presenter.updateItem()
    }
}

