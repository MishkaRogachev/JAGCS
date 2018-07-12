import QtQuick 2.6

import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    enabled: vehicle.online
}
