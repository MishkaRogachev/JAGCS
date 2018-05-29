import QtQuick 2.6

TextField {
    id: control

    placeholderText: qsTr("Type filter here")

    Button {
        anchors.right: parent.right
        anchors.verticalCenter: parent.VerticalCenter
        flat: true
        visible: control.text.length > 0
        iconSource: "qrc:/ui/erase.svg"
        onClicked: control.clear()
    }
}
