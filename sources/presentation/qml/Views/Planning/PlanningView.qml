import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "../Map"
import "../VerticalProfile"
import "Mission"

Controls.Pane {
    id: root

    property bool profileVisibe: false

    MissionView {
        id: mission
        objectName: "mission"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: profile.top
    }

    MapView {
        id: map
        objectName: "map"
        anchors.left: mission.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: profile.top
        anchors.leftMargin: palette.margins
    }

    VerticalProfileView {
        id: profile
        objectName: "profile"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: palette.margins
        height: profileVisibe ? parent.height / 3 : 0
    }

    Controls.Button {
        iconSource: profileVisibe ? "qrc:/ui/down.svg" : "qrc:/ui/up.svg"
        onClicked: profileVisibe = !profileVisibe
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }
}
