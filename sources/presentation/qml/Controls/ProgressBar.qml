import QtQuick 2.6
import QtQuick.Controls 2.0

import "./"

ProgressBar {
      id: control

      background: Rectangle {
          width: control.availableWidth
          implicitWidth: palette.controlBaseSize * 6
          implicitHeight: palette.controlBaseSize / 4
          radius: height / 2
          color: control.enabled ? palette.sunkenColor : palette.disabledColor
      }

      contentItem: Item {
          implicitWidth: background.implicitWidth
          implicitHeight: background.implicitHeight

          Rectangle {
              width: control.visualPosition * background.width
              height: parent.height
              radius: height / 2
              color: palette.selectionColor
          }
      }
  }
