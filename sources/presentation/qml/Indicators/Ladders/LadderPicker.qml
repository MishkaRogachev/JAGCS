import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import ".."

Item {
    id: root

    property bool mirrored: parent.mirrored
    property bool overboardEnabled: false
    property real inputValue: 0
    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property var args: [ inputValue ]
    readonly property real offset: area.mouseY - area.oldY
    readonly property real offsetBordered: Math.min(Math.max(offset, -height / 2), height / 2)
    property color color: {
        if (status == Command.Rejected) return customPalette.dangerColor;
        if (status == Command.Sending) return customPalette.cautionColor;
        if (status == Command.Completed) return customPalette.positiveColor;
        return customPalette.activeMissionColor;
    }

    onColorChanged: arrowCanvas.requestPaint()
    onOffsetBorderedChanged: inputValue = root.parent.mapFromRange(height / 2 - offsetBordered)

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
        property int multiplier: {
            if (Math.abs(offset) > 100) return 100;
            if (Math.abs(offset) > 10) return 10;
            return 1;
        }
        repeat: true
        interval: 400
        running: offset != offsetBordered && overboardEnabled
        onTriggered: inputValue = Math.floor(inputValue / multiplier +
                                             (offset > 0 ? -1 : 1)) * multiplier
    }

    Controls.ColoredIcon {
        anchors.left: mirrored ? undefined : parent.left
        anchors.right: mirrored ? parent.right : undefined
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: -root.height / 5
        source: "qrc:/icons/min_up.svg"
        color: root.color
        visible: enabled
    }

    Controls.ColoredIcon {
        anchors.left: mirrored ? undefined : parent.left
        anchors.right: mirrored ? parent.right : undefined
        anchors.verticalCenter: root.verticalCenter
        anchors.verticalCenterOffset: root.height / 5
        source: "qrc:/icons/min_down.svg"
        color: root.color
        visible: enabled
    }

    Item {
        id: pickerItem
        anchors.left: mirrored ? undefined : parent.right
        anchors.right: mirrored ? parent.left : undefined
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: offsetBordered
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
