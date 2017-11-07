import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

GridLayout {
    id: grid

    property int preferredWidth: palette.controlBaseSize * 17

    property string version: qsTr("(undefined version)")
    property string revision: qsTr("Undefined")
    property string qtVersion: qsTr("Undefined")

    columns: 2
    rowSpacing: palette.spacing
    columnSpacing: palette.spacing

    Controls.Label {
        text: "Just another ground control station " + version
        font.bold: true
        Layout.columnSpan: 2
        Layout.leftMargin: palette.margins
    }

    Controls.Label {
        text: qsTr("Revision")
        Layout.leftMargin: palette.margins
    }

    Controls.Label {
        text: revision
    }

    Controls.Label {
        text: qsTr("Qt version")
        Layout.leftMargin: palette.margins
    }

    Controls.Label {
        text: qtVersion
    }

    Controls.Label {
        text: qsTr("Contacts")
        Layout.leftMargin: palette.margins
    }

    Controls.Link {
        text: "<a href='mailto:mishkarogachev@gmail.com'>mishkarogachev@gmail.com</a>"
    }

    Controls.Label {
        text: qsTr("Web site")
        Layout.leftMargin: palette.margins
    }

    Controls.Link {
        text: "<a href='https://github.com/MishkaRogachev/JAGCS'>https://github.com/MishkaRogachev/JAGCS</a>"
    }

    Controls.Label {
        text: qsTr("Donate")
        Layout.leftMargin: palette.margins
    }

    Controls.Link {
        text: "<a href='https://www.paypal.me/MishkaRogachev'>https://www.paypal.me/MishkaRogachev</a>"
    }

    Controls.Label {
        text: qsTr("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.")
        Layout.columnSpan: 2
        wrapMode: Text.WordWrap
        Layout.maximumWidth: root.width - palette.margins * 2
        Layout.leftMargin: palette.margins
    }
}
