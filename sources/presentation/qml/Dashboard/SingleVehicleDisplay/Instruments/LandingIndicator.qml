import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls
import Industrial.Indicators 1.0 as Indicators
import "../../DashboardControls" as DashboardControls

BaseInstrument {
    id: root

    Connections {
        target: display
        onUpdateCommandStatus: {
            switch (command) {
            case Command.Land:
                landButton.status = status;
                break;
            case Command.GoAround:
                goAroundButton.status = status;
                break;
            default:
                break;
            }
        }
    }

    implicitHeight: width * 0.6

    Indicators.ValueLabel {
        anchors.top: parent.top
        anchors.left: parent.left
        prefix: qsTr("DEV X")
        value: vehicle.landingSystem.deviationX
        width: parent.width * 0.2
    }

    Indicators.ValueLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        prefix: qsTr("DEV Y")
        value: vehicle.landingSystem.deviationY
        width: parent.width * 0.2
    }

    Indicators.ValueLabel {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.rightMargin: itemMenuButton.width
        prefix: qsTr("SIZE X")
        value: vehicle.landingSystem.sizeX
        width: parent.width * 0.2
    }

    Indicators.ValueLabel {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        prefix: qsTr("SIZE Y")
        value: vehicle.landingSystem.sizeY
        width: parent.width * 0.2
    }

    Indicators.LandingIndicator {
        anchors.centerIn: parent
        height: parent.height - industrial.padding
        width: height
        deviationX: vehicle.landingSystem.deviationX
        deviationY: vehicle.landingSystem.deviationY
        sizeX: vehicle.landingSystem.sizeX
        sizeY: vehicle.landingSystem.sizeY
    }

    Indicators.DistanceLabel {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        prefix: qsTr("DIST")
        distance: vehicle.landingSystem.distance
        width: parent.width * 0.2
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        spacing: 0

        DashboardControls.CommandButton {
            id: landButton
            command: Command.Land
            iconSource: "qrc:/icons/landing.svg"
            tipText: qsTr("Landing")
            flat: true
            args: []
        }

        DashboardControls.CommandButton {
            id: goAroundButton
            command: Command.GoAround
            iconSource: "qrc:/icons/go_around.svg"
            tipText: qsTr("Go around")
            flat: true
            args: []
        }
    }
}
