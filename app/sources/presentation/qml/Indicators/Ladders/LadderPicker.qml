import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls
import ".."

Item {
    id: root

    property bool mirrored: parent.mirrored

    property int command: Command.UnknownCommand
    property int status: Command.Idle
    property real value: 0
    property real inputValue: 0
    property var args: [ inputValue ]
    property color color: {
        if (status == Command.Rejected) return customPalette.dangerColor;
        if (status == Command.Sending) return customPalette.cautionColor;
        if (status == Command.Completed) return customPalette.positiveColor;
        return customPalette.activeMissionColor;
    }

    onColorChanged: arrowCanvas.requestPaint()
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
        readonly property bool mouseXInLadder: area.mouseX > 0 && area.mouseX < width
        anchors.fill: parent
        preventStealing: true
        onPressed: {
            if (status == Command.Sending) presenter.rejectCommand(command);
            inputValue = root.value;
            oldY = mouseY;
        }
        onPositionChanged: {
            var newValue = root.parent.mapFromRange(height - mouseY) +
                    root.value - root.parent.mapFromRange(height - oldY);
            inputValue = newValue;
            // TODO: integral scale for overboard values
        }
        onReleased: {
            if (mouseXInLadder && inputValue !== root.value) {
                presenter.executeCommand(command, args);
            }
            oldY = 0;
        }
    }

    Item {
        anchors.left: mirrored ? undefined : parent.left
        anchors.right: mirrored ? parent.right : undefined
        width: sizings.controlBaseSize
        height: parent.height

        Controls.ColoredIcon {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -parent.height / 5
            source: "qrc:/icons/min_up.svg"
            color: status == Command.Idle ? customPalette.textColor : root.color
            visible: enabled
        }

        Controls.ColoredIcon {
            anchors.centerIn: parent
            anchors.verticalCenterOffset: parent.height / 5
            source: "qrc:/icons/min_down.svg"
            color: status == Command.Idle ? customPalette.textColor : root.color
            visible: enabled
        }
    }

    Item {
        id: pickerItem
        anchors.left: mirrored ? undefined : parent.right
        anchors.right: mirrored ? parent.left : undefined
        y: root.height - Math.min(Math.max(root.parent.mapToRange(
                                               inputValue), 0), root.height) - height / 2
        width: arrowCanvas.width + label.width + sizings.padding
        height: label.height
        visible: area.pressed && area.mouseXInLadder

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
