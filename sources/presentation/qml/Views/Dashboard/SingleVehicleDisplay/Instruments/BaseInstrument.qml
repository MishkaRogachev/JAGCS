import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.Pane {
    id: root

    enabled: vehicle.online
}
