import QtQuick 2.6
import JAGCS 1.0

import "../Controls" as Controls

import "Status"
import "Control"
import "Planning"
import "Settings"

Item {
    id: main

    property int mode: MainPresenter.NoMode

    anchors.fill: parent

    StatusView {
        id: status
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        objectName: "statusbar"
        z: 1000
    }

    Loader {
        anchors.fill: parent
        anchors.topMargin: status.height
        sourceComponent: {
            switch (mode) {
            case MainPresenter.Control: return controlComponent;
            case MainPresenter.Planning: return planningComponent;
            case MainPresenter.Settings: return settingsComponent;
            }
        }
    }

    Component{
        id: controlComponent

        ControlView { objectName: "control" }
    }

    Component{
        id: planningComponent

        PlanningView { objectName: "planning" }
    }

    Component{
        id: settingsComponent

        SettingsView { objectName: "settings" }
    }
}
