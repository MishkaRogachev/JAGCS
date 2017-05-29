import QtQuick 2.6
import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property string name
    property int mavId

    property bool online
    property bool armed
    property string modeString

    property real pitch
    property real roll

    property real course
    property real heading
}
