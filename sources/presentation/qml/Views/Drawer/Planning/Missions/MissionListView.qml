import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: missionList

    property alias missions: list.model

    implicitWidth: headerRow.height + sizings.spacing + list.contentWidth
    implicitHeight: list.contentHeight

    MissionListPresenter {
        id: presenter
        view: missionList
    }

    RowLayout {
        id: headerRow
        width: parent.width
        spacing: sizings.spacing

        Controls.TextField {
            id: hostNameItem
            placeholderText: qsTr("Type filter here")
            onTextChanged: missions.filter(text)
            Layout.fillWidth: true
        }

        Controls.Button {
            iconSource: "qrc:/icons/add.svg"
            tipText: qsTr("Add Mission")
            onClicked: presenter.addMission()
            Layout.alignment: Qt.AlignRight
        }
    }

    ListView {
        id: list
        anchors.fill: parent
        anchors.topMargin: headerRow.height + sizings.spacing
        spacing: sizings.spacing
        flickableDirection: Flickable.AutoFlickIfNeeded
        boundsBehavior: Flickable.StopAtBounds
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {
            visible: parent.contentHeight > parent.height
        }

        delegate: MissionView {
            width: parent.width
            missionId: model.missionId
        }

        Controls.Label {
            id: label
            text: qsTr("No items present")
            visible: list.count === 0
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
        }
    }
}
