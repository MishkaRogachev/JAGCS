import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: linkList

    property alias linkIds: list.model // TODO: change on links

    implicitWidth: headerRow.height + sizings.spacing + list.contentWidth
    implicitHeight: list.contentHeight

    LinkListPresenter {
        id: presenter
        view: linkList
        Component.onCompleted: updateLinks()
    }

    RowLayout {
        id: headerRow
        width: parent.width
        spacing: sizings.spacing

        Controls.TextField {
            enabled: false// TODO: filter field
            id: hostNameItem
            placeholderText: qsTr("Type filter here")
            onTextChanged: missions.filter(text)
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/add.svg"
            tipText: qsTr("Add Link")
            onClicked: if (!addMenu.visible) addMenu.open()

            Controls.Menu {
                id: addMenu
                implicitWidth: parent.width
                y: parent.height

                Controls.MenuItem {
                    text: qsTr("Udp")
                    implicitWidth: parent.width
                    onTriggered: presenter.addUdpLink()
                }

                Controls.MenuItem {
                    text: qsTr("Serial")
                    implicitWidth: parent.width
                    onTriggered: presenter.addSerialLink()
                }
            }
            Layout.alignment: Qt.AlignRight
        }
    }

    Item {
        anchors.fill: parent
        anchors.topMargin: headerRow.height + sizings.spacing
        clip: true

        ListView {
            id: list
            anchors.fill: parent
            anchors.margins: sizings.shadowSize
            spacing: sizings.spacing
            flickableDirection: Flickable.AutoFlickIfNeeded
            boundsBehavior: Flickable.StopAtBounds

            Controls.ScrollBar.vertical: Controls.ScrollBar {
                visible: parent.contentHeight > parent.height
            }

            delegate: LinkView {
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                linkId: modelData//model.missionId
            }
        }

        Controls.Label {
            anchors.centerIn: parent
            text: qsTr("No links present")
            visible: list.count === 0
        }
    }
}
