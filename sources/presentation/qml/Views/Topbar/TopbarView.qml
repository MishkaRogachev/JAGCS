import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

Rectangle {
    id: topbar

    color: palette.raisedColor
    height: palette.controlBaseSize

    TopbarPresenter {
        view: topbar
    }
}
