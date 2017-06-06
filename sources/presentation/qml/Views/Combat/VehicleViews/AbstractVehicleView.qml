import QtQuick 2.6
import "qrc:/Controls" as Controls

Controls.Frame {
    id: root

    property string name
    property int mavId

    property bool online
    property bool armed
    property string mode

    property real ahrs_pitch
    property real ahrs_roll

    property real satellite_course
    property real compass_heading
}
