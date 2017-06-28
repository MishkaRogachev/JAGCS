import QtQuick 2.6

FdLabel {
    id: root

    property real distance: 0

    value: distance < 1000 ? distance : distance / 1000
    digits: distance < 1000 ? 0 : 1
    suffix: distance < 1000 ? qsTr("m") : qsTr("km")
}
