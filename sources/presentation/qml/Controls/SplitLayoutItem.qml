import QtQuick 2.6
import QtQuick.Layouts 1.3

import "./" as Custom

Item {
    id: root

    property Item contentItem: children[children.length - 1]

    implicitWidth: contentItem.implicitWidth
    implicitHeight: contentItem.implicitHeight
    onWidthChanged: contentItem.width = width
    onHeightChanged: contentItem.height = height
    onImplicitHeightChanged: split.forceLayout()

    Custom.Button {
        iconSource: contentItem.visible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
        onClicked: contentItem.visible = !contentItem.visible;
        z: 1
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
