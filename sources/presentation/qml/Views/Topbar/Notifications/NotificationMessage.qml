import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Popup {
    id: popup

    property string text: ""
    property int type: 0

    function show(message) {
        text = message.message;
        type = message.type;
        open();
    }

    function drop() {
        text = "";
        type = 0;
        close();
    }

    //height: pane.implicitHeight
    closePolicy: Controls.Popup.NoAutoClose

    RowLayout {
        anchors.fill: parent
        spacing: sizings.spacing

        Controls.Label {
            text: popup.text
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
