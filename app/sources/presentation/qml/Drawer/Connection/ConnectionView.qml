import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "Links"

Item {
    id: connection

    property int selectedLinkId: 0

    implicitWidth: sizings.controlBaseSize * 10

    Connections {
        target: drawer
        onCloseSubmode: selectedLinkId = 0
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
