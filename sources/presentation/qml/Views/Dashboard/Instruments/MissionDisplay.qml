import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../CommandControls" as CommandControls

Controls.Pane {
    id: missionDisplay

    property int current: -1
    property int count: 0
    property int status: 0

    enabled: online
    onCurrentChanged: box.currentIndex = current

    MissionDisplayPresenter {
        id: presenter
        view: missionDisplay
        Component.onCompleted: setVehicle(vehicleId)
    }

    RowLayout {
        anchors.centerIn: parent
        width: parent.width
        spacing: sizings.spacing

        Controls.Label {
            text: qsTr("WP")
            Layout.fillWidth: true
        }

        Controls.Button {
            tipText: qsTr("Goto left")
            iconSource: "qrc:/icons/left.svg"
            enabled: current > 1
            onClicked: presenter.goTo(current - 1)
        }

         Controls.ComboBox {
             id: box
             model: count
         }

        Controls.Button {
            tipText: qsTr("Goto right")
            iconSource: "qrc:/icons/right.svg"
            enabled: current < count - 1
            onClicked: presenter.goTo(current + 1)
        }
    }
}
