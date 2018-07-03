import QtQuick 2.6
import QtQuick.Templates 2.2 as T
import QtQuick.Layouts 1.3

ColumnLayout {
    id: control

    property alias model: repeater.model
    property int currentIndex: 0

    spacing: sizings.padding / 2

    Repeater {
        id: repeater

        Button {
            Layout.preferredWidth: sizings.controlBaseSize * 7
            text: modelData
            onClicked: if (!highlighted) currentIndex = index
            highlighted: currentIndex == index
        }
    }
}
