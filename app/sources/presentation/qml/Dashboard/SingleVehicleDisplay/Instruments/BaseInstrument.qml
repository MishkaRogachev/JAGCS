import QtQuick 2.6

import Industrial.Controls 1.0 as Controls

Controls.Frame {
    id: root

    enabled: vehicle.online
}
