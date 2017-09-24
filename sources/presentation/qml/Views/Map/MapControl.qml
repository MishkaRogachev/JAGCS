import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    z: 10000

    Controls.Button {
        iconSource: "qrc:/icons/compas.svg"
        onClicked: map.bearing = 0
    }
}
