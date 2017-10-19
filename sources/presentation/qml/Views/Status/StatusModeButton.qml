import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Controls.Button {
    id: root

    property int mode: MainPresenter.NoMode

    onClicked: {
        if (highlighted) return;

        parent.enabled = false;
        setMode(mode);
    }
    highlighted: main.mode === mode
    onHighlightedChanged: if (highlighted) parent.enabled = true;
    flat: true
}
