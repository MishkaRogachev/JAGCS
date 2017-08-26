import QtQuick 2.6

Button {
    id: root

    property alias picking: root.checked

    signal picked(var coordinate)

    iconSource: "qrc:/icons/map-marker.svg"
    checkable: true
    onPickingChanged: map.picking = picking
    Component.onDestruction: map.dropPicker();
    onVisibleChanged: if (!visible) map.dropPicker();

    Connections {
        target: map
        onPicked: {
            if (!root.checked) return;

            root.checked = false;
            map.picking = false;
            picked(coordinate);
        }
    }
}
