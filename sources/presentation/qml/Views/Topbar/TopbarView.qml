import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: topbar

    property string contextText
    property var vehicles: []

    color: palette.raisedColor
    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
        Component.onCompleted: updateVehicles()
    }

    RowLayout {
        anchors.left: parent.left
        anchors.leftMargin: sizings.margins
        anchors.verticalCenter: parent.verticalCenter

        Controls.Label {
            text: qsTr("MAV")
        }

        Controls.ComboBox {
            model: vehicles
            textRole: "name"
            onActivated: dashboard.setActiveVehicle(vehicles[currentIndex].id)
        }
    }

    RowLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: menuButton.right
        width: menuDrawer.width
        clip: true
        visible: menu.visible

        Controls.Button {
            tipText: qsTr("Home")
            iconSource: "qrc:/icons/home.svg"
            flat: true
            enabled: !menu.atHome
            onClicked: menu.home()
        }

        Repeater {
            model: contextModel

            Controls.Button {
                text: model.text
                flat: true
                visible: index + 1 < contextModel.count
                onClicked: menu.backOut(index)
            }
        }

        Controls.Label {
            text: contextText
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
        }
    }

    Controls.Button {
        id: menuButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        tipText: menu.visible ? qsTr("Menu") : qsTr("Close menu")
        iconSource: menu.visible ? "qrc:/icons/right.svg" : "qrc:/icons/burger.svg"
        flat: true
        onClicked: menu.visible ? menuDrawer.close() : menuDrawer.open()
    }
}
