import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

Button {
    id: root

    signal picked(var coordinate)

    function pick() { checked = true; }

    iconSource: "qrc:/icons/map-marker.svg"
    checkable: true

    Connections {
        target: map
        onPicked: {
            if (!pickButton.checked) return;
            root.checked = false;
            picked(coordinate)
        }
        onCanceled: if (!pickButton.checked) root.checked = false;
    }
}
