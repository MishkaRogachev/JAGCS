import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "./"

ColumnLayout {
    id: control

    property alias model: repeater.model
    property int currentIndex: -1

    ButtonGroup {
        id: group
    }

    Repeater {
        id: repeater

        Button {
            checkable: true
            Layout.preferredWidth: palette.controlBaseWidth
            text: modelData
            Component.onCompleted: {
                group.addButton(this)
                if (index == 0) checked =  true;
            }
            onCheckedChanged: {
                if (checked) currentIndex = index;
            }
        }
    }
}
