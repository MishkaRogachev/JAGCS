import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "Links"

Item {
    id: connection

    property int selectedLinkId: 0

    implicitWidth: sizings.controlBaseSize * 11
    implicitHeight: selectedLinkId > 0 ? linkEdit.implicitHeight : linkList.implicitHeight

    Connections {
        target: map

        onSelectItem: {
            if (selectedLinkId != missionId) selectedLinkId = missionId;
            linkEdit.selectedItemId = itemId;
        }
    }

    PlanningPresenter {
        id: presenter
        view: connection
        Component.onCompleted: updateVehicles()
    }

    LinkListView {
        id: linkList
        anchors.fill: parent
        visible: selectedLinkId == 0
    }

    LinkEditView {
        id: linkEdit
        anchors.fill: parent
        linkId: selectedLinkId
        visible: selectedLinkId > 0
    }
}
