import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Martial"

ColumnLayout {
    id: root

    //property QtObject presenter: factory.createConnectionStatusPresenter(root)

    Label {
        text: "Rx:"
    }

    Label {
        text: "Tx:"
    }
}
