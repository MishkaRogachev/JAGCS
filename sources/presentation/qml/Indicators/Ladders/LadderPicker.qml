import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import ".."

Item {
    id: root

    property bool mirrored: parent.mirrored
    property real inputValue: 0
    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: [ inputValue ]
    readonly property real offset: Math.min(Math.max(area.mouseY - area.oldY, -height / 2),
                                            height / 2)
    property color color: {
        if (status == Command.Rejected) return customPalette.dangerColor;
        if (status == Command.Sending) return customPalette.cautionColor;
        if (status == Command.Completed) return customPalette.positiveColor;
        return customPalette.activeMissionColor;
    }

    onColorChanged: arrowCanvas.requestPaint()
    onOffsetChanged: inputValue = root.parent.mapFromRange(height / 2 - offset)

    onStatusChanged: {
        if (status == Command.Completed ||
            status == Command.Rejected) timer.start()
    }
    onCommandChanged: {
        if (timer.running) timer.stop();
        status = Command.Idle;
    }

    Timer {
        id: timer
        onTriggered: status = Command.Idle
    }

    MouseArea {
        id: area
        property real oldY: 0
        anchors.fill: parent
        preventStealing: true
        onPressed: {
            if (status == Command.Sending) presenter.rejectCommand(command);
            inputValue = root.parent.value;
            oldY = mouseY;
        }
        onReleased: {
            if (inputValue !== root.parent.value) presenter.executeCommand(command, args);
            oldY = 0;
        }
    }

    Timer {
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
        width: arrowCanvas.width + label.width + sizings.padding
        height: label.height
        visible: area.pressed

        Controls.Shadow {
            anchors.fill: rect
            source: parent
        }

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
            id: rect
            anchors.fill: parent
            anchors.rightMargin: mirrored ? arrowCanvas.width : 0
            anchors.leftMargin: mirrored ? 0 : arrowCanvas.width - 1
            color: root.color
        }

        ValueLabel {
            id: label
            anchors.right: mirrored ? undefined : parent.right
            anchors.left: mirrored ? parent.left : undefined
            anchors.margins: sizings.padding / 2
            value: inputValue
            color: customPalette.selectedTextColor
        }
    }
}
