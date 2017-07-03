import QtQuick 2.6
import QtQuick.Layouts 1.3

import "./" as Custom

Item {
    id: root

    property Item substrate: children[1]
    property int spacing: palette.spacing

    onChildrenChanged: forceLayout()
    onWidthChanged: forceLayout()
    onHeightChanged: forceLayout()

    function forceLayout() {
        var offset = 0;

        for (var i = 0; i < children.length; ++i) {
            var item = children[i];
            if (!item.visible) continue;

            if (item === substrate) {
                item.x = 0;
                item.y = 0;
                item.width = root.width;
                item.height = root.height;
            }
            else {
                item.width = item.implicitWidth;
                item.x = root.width - item.width;
                offset += item.implicitHeight + spacing;
                item.y = root.height - offset;
                item.height = item.implicitHeight;
            }
        }
    }

    Repeater {
        model: children.length

        Custom.Button {
            Component.onCompleted: console.log(index)
            iconSource: children[index].visible ? "qrc:/icons/hide.svg" : "qrc:/icons/show.svg"
            onClicked: children[index].visible = !children[index].visible;
            x: children[index].x
            y: children[index].y
            width: 50
            height: 50
            z: 1
        }
    }
}
