import QtQuick 2.6

ValueLabel {
    id: root

    property real distance: 0
    readonly property string distancePrefix: distance < 1000 ? qsTr("m") : qsTr("km")

    prefix: distancePrefix
    value: distance < 1000 ? distance : distance / 1000
    digits: distance < 1000 ? 0 : 1
}
