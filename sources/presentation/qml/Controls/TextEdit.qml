import QtQuick 2.6

import "../Shaders" as Shaders

TextField {
    id: control

    property string originalText

    text: originalText
    onOriginalTextChanged: text = originalText
    rightPadding: restoreButton.width

    Button {
        id: restoreButton
        flat: true
        anchors.right: parent.right
        height: parent.height
        enabled: control.text != originalText
        iconSource: "qrc:/icons/restore.svg"
        onClicked: control.text = originalText
    }
}
