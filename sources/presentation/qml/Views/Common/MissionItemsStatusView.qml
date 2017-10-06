import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls
import "qrc:/Shaders" as Shaders

Flickable {
    id: root

    property int selectedItem: -1

    property alias items: repeater.model

    signal selectItem(int sequence)

    function updateItem(item) {
        var view = repeater.itemAt(item.sequence);
        if (!view) return;

        view.current = item.current;
        view.reached = item.reached;
        view.status = item.status;
        view.command = item.command;
    }

    implicitHeight: row.height
    contentWidth: row.width
    boundsBehavior: Flickable.StopAtBounds
    clip: true

    RowLayout {
        id: row
        spacing: 1

        Controls.Label {
            visible: items.length === 0
            text: qsTr("No waypoints")
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: root.width
        }

        Repeater {
            id: repeater
            model: []

            MissionItemView {
                selected: selectedItem === sequence
                current: modelData.current
                reached: modelData.reached
                status: modelData.status
                command: modelData.command
                sequence: modelData.sequence
                onSelectedChanged: {
                    if (!selected) return;

                    if (x + width > root.width + root.contentX) {
                        root.contentX = x + width - root.width;
                    }
                    else if (x < root.contentX) {
                        root.contentX = x;
                    }
                }
                onSelectionRequest: selectItem(sequence)
            }
        }
    }

    Shaders.Hatch {
        anchors.fill: parent
        color: palette.sunkenColor
        visible: !root.enabled
    }
}
