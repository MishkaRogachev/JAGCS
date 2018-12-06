import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

import "Links"
import "MavLinkSettings"

Item {
    id: connection

    property int selectedLinkId: 0

    implicitWidth: controlSize.baseSize * 10

    Connections {
        target: drawer
        onCloseSubmode: selectedLinkId = 0
    }
    
    MavLinkSettingsView {
        id: mavLinkSettings
        anchors { left: parent.left; right: parent.right; top: parent.top; margins: controlSize.shadowSize }
        visible: selectedLinkId == 0
    }

    LinkListView {
        id: linkList
        anchors.fill: parent
        anchors.topMargin: mavLinkSettings.height + controlSize.spacing
        visible: selectedLinkId == 0
    }

    LinkEditView {
        id: linkEdit
        anchors.fill: parent
        linkId: selectedLinkId
        visible: selectedLinkId > 0
    }
}
