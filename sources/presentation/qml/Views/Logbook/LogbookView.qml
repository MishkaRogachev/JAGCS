import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Item {
    id: root

    property bool maximized: false
    property real logHeightFactor: 0.5

    Rectangle {
        anchors.left: parent.left
        anchors.right: button.left
        anchors.top: parent.top
        height: maximized ? main.height * logHeightFactor : root.height
    }
 
    Controls.Button {
        id: button
        anchors.right: parent.right
        anchors.top: parent.top
        iconSource: maximized ? "qrc:/ui/up.svg" : "qrc:/ui/down.svg"
        onClicked: maximized = !maximized
    }
}
