import QtQuick 2.6

TextField {
    id: control

    placeholderText: qsTr("Type filter here")

    Button {
        anchors.right: parent.right
        anchors.verticalCenter: parent.VerticalCenter
        iconSource: "qrc:/ui/erase.svg"
        tipText: qsTr("Clear filter")
        flat: true
        visible: control.text.length > 0
        onClicked: control.clear()
    }
}
