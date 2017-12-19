import QtQuick 2.6

AttitudeIndicator {
    id: ah

    property bool armed: false

    PlaneMark {
        id: mark
        anchors.centerIn: parent
        width: parent.width - sizings.margins
        effectiveHeight: ah.effectiveHeight
        pitch: pitchInverted ? 0 : -ah.pitch
        roll: rollInverted ? -ah.roll : 0
        markColor: armed ? palette.selectedTextColor : palette.dangerColor
        markWidth: 1.5
    }
}
