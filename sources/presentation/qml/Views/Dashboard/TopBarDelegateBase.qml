import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls    

RowLayout {
    id: topbarDelegate

    spacing: sizings.spacing
    layoutDirection: Qt.RightToLeft

    Controls.Button {
        iconSource: dashboard.dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                                 "qrc:/icons/show_dashboard.svg"
        tipText: (dashboard.dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                                               " " + qsTr("dashboard")
        flat: true
        onClicked: dashboard.dashboardVisible = !dashboard.dashboardVisible
    }
}
