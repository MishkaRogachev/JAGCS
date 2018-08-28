import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Item {
    id: linkList

    LinkListPresenter {
        id: presenter
    }

    ListView {
        id: list
        model: presenter.links
        anchors.fill: parent
        anchors.margins: sizings.shadowSize
        anchors.bottomMargin: addButton.height
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: LinkView {
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            presenter: model.display
        }
    }

    Controls.Label {
        anchors.centerIn: parent
        text: qsTr("No links present")
        visible: list.count === 0
    }

    Controls.RoundButton {
        id: addButton
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        iconSource: "qrc:/ui/plus.svg"
        tipText: qsTr("Add Mission")
        onClicked: if (!addMenu.visible) addMenu.open()

        Controls.Menu {
            id: addMenu
            x: (parent.width - width) / 2
            width: list.width

            Controls.MenuItem {
                text: qsTr("Serial")
                implicitWidth: parent.width
                onTriggered: presenter.addSerialLink()
            }

            Controls.MenuItem {
                text: qsTr("Udp")
                implicitWidth: parent.width
                onTriggered: presenter.addUdpLink()
            }

            Controls.MenuItem {
                text: qsTr("Tcp")
                implicitWidth: parent.width
                onTriggered: presenter.addTcpLink()
            }

            Controls.MenuItem {
                text: qsTr("Bluetooth")
                implicitWidth: parent.width
                onTriggered: presenter.addBluetoothLink()
            }
        }
    }
}
