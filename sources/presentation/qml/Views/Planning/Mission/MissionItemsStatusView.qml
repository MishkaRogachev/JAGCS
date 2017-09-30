import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Flickable {
    id: root

    property var items: []
    property int selectedItem: -1

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

            Item {
                Layout.minimumWidth: palette.controlBaseSize
                Layout.minimumHeight: palette.controlBaseSize

                property bool selected: selectedItem == index
                onSelectedChanged: {
                    if (!selected) return;

                    if (x + width > root.width + root.contentX) {
                        root.contentX = x + width - root.width;
                    }
                    else if (x < root.contentX) {
                        root.contentX = x;
                    }
                }

                Rectangle {
                    anchors.centerIn: parent
                    width: parent.height
                    height: width
                    radius: width / 2
                    color: selected ? palette.selectionColor : palette.raisedColor
                    border.color: {
                        switch (parseInt(modelData)) {
                        case MissionItem.Actual: return palette.positiveColor;
                        case MissionItem.StatusNone: return palette.sunkenColor;
                        case MissionItem.Downloading:
                        case MissionItem.Uploading: return palette.cautionColor;
                        case MissionItem.NotActual:
                        default: return palette.dangerColor;
                        }
                    }
                    border.width: 4

                    Controls.Label { // TODO: mode icon
                        text: index
                        color: selected ? palette.selectedTextColor : palette.textColor
                        anchors.centerIn: parent
                        font.bold: true
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: selectItem(index)
                    }
                }
            }
        }
    }
}
