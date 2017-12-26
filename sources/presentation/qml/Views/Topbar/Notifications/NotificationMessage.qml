import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: message

    property string text: ""
    property int type: 0

    function show(msg) {
        text = msg.message;
        type = msg.type;
        open();
    }

    function drop() {
        text = "";
        type = 0;
        close();
    }

    width: pane.implicitWidth
    height: pane.implicitHeight
    closePolicy: Controls.Popup.NoAutoClose

    Controls.Pane {
        id: pane
        anchors.centerIn: parent

        RowLayout {
            spacing: sizings.spacing

            Controls.Label {
                text: message.text
                color: {
                    switch (type) {
                    case LogMessage.Positive:
                        return palette.positiveColor;
                    case LogMessage.Warning:
                        return palette.cautionColor;
                    case LogMessage.Critical:
                        return palette.dangerColor;
                    case LogMessage.Common:
                    default:
                        return palette.textColor;
                    }
                }
                Layout.fillWidth: true
            }

            Controls.Button {
                iconSource: "qrc:/icons/remove.svg"
                flat: true
                onClicked: drop()
            }
        }
    }
}
