import QtQuick 2.6
import QtQuick.Controls 2.0

Button { // TODO: controls to my style
    id: button

    property alias iconSource: image.source

    contentItem: Item {
        implicitWidth: row.width
        implicitHeight: row.height

        Row {
            id: row
            anchors.centerIn: parent
            height: parent.availableHeight
            spacing: 5

            Image {
                id: image
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                font: button.font
                text: button.text
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}
