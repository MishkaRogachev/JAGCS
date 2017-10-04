import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Flickable { // FIXME:
    id: root

    property var items: []
    property int selectedItem: -1
    property int currentItem: -1

    signal selectItem(int sequence)

    implicitHeight: row.height
    contentWidth: row.width
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    RowLayout {
        id: row
        spacing: 1

        Controls.Label {
            visible: items.length == 0
            text: qsTr("No waypoints")
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: root.width
        }

        Repeater {
            model: items

            MissionItemView {
                item: modelData
                selected: selectedItem === item.sequence
                current: currentItem === item.sequence
                onSelectedChanged: {
                    if (!selected) return;

                    if (x + width > root.width + root.contentX) {
                        root.contentX = x + width - root.width;
                    }
                    else if (x < root.contentX) {
                        root.contentX = x;
                    }
                }
                onSelectionRequest: selectItem(item.sequence)
            }
        }
    }
}
