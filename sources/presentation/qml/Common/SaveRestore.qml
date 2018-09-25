import QtQuick 2.6
import QtQuick.Layouts 1.3

import Industrial.Controls 1.0 as Controls

RowLayout {
    id: root

    signal save()
    signal restore()

    spacing: 0

    Controls.Button {
        iconSource: "qrc:/icons/save.svg"
        tipText: qsTr("Save")
        flat: true
        onClicked: save()
    }

    Controls.Button {
        iconSource: "qrc:/icons/restore.svg"
        tipText: qsTr("Restore")
        flat: true
        onClicked: restore()
    }
}
