import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

Rectangle {
    id: root

    color: palette.raisedColor
    height: palette.controlBaseSize

    Component.onCompleted: {
        factory.createTopbarPresenter()
        home();
    }

}
