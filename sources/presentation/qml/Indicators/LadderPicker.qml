import QtQuick 2.6
import JAGCS 1.0

import "../Controls" as Controls

Item {
    id: root

    property bool mirrored: parent.mirrored
    property color color: customPalette.activeMissionColor
    property real inputValue: 0
    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: [ inputValue ]
    readonly property real offset: Math.min(Math.max(area.mouseY - area.oldY, -height / 2),
                                            height / 2)

    onOffsetChanged: inputValue = root.parent.mapFromRange(height / 2 - offset)

    MouseArea {
        id: area
        property real oldY: 0
        anchors.fill: parent
        preventStealing: true
        onPressed: {
            if (status == Command.Sending) presenter.rejectCommand(command);
            oldY = mouseY;
        }
        onReleased: {
            if (inputValue !== root.parent.value) presenter.executeCommand(command, args);
            oldY = 0;
        }
    }

    Timer {
        id: timer
        repeat: true
        running: Math.abs(offset) == height / 2
        onRunningChanged: interval = 500
        onTriggered: {
            offset > 0 ? inputValue-- : inputValue++;
            if (interval > 10) interval = interval / 2;
        }
    }

    Item {
        id: pickerItem
        anchors.left: mirrored ? undefined : parent.right
        anchors.right: mirrored ? parent.left : undefined
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: offset
        width: parent.width
        height: label.height
        visible: area.pressed

        Canvas {
            id: arrowCanvas
            width: root.parent.majorTickSize
            height: parent.height
            anchors.left: mirrored ? undefined : parent.left
            anchors.right: mirrored ? parent.right : undefined
            onPaint: {
                var ctx = getContext('2d');

                ctx.clearRect(0, 0, width, height);
                ctx.lineWidth = 2;

                ctx.fillStyle = color;
                ctx.beginPath();
                ctx.moveTo(mirrored ? 0 : width, 0);
                ctx.lineTo(mirrored ? width : 0, height / 2);
                ctx.lineTo(mirrored ? 0 : width, height);
                ctx.fill();
            }
        }

        Rectangle {
            anchors.fill: parent
            anchors.rightMargin: mirrored ? arrowCanvas.width : 0
            anchors.leftMargin: mirrored ? 0 : arrowCanvas.width - 1
            color: root.color
        }

        ValueLabel {
            id: label
            width: parent.width
            value: inputValue
            color: customPalette.selectedTextColor
        }
    }
}
