import QtQuick 2.6
import QtQuick.Controls 2.0

Rectangle {
    id: root

    property QtObject presenter: factory.createStatusPresenter(root)

    color: "#455A64"

    Row {
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.margins: 5

        Button {
            text: qsTr("Quit")
            anchors.verticalCenter: parent.verticalCenter
            onClicked: presenter.quit()
        }
    }
}
