import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.Pane {
    id: root

    property int minimumHeight: implicitHeight
    property int maximumHeight: implicitHeight

    clip: true
}
