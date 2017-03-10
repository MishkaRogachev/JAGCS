import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Frame {
    id: root

    property string version: qsTr("(undefined version)")
    property string revision: qsTr("Undefined")
    property string qtVersion: qsTr("Undefined")

    GridLayout {
        columns: 2
        rowSpacing: palette.spacing

        Label {
            text: "Just another ground control station " + version
            font.bold: true
            Layout.columnSpan: 2
        }

        Label {
            text: qsTr("Revision")
        }

        Label {
            text: revision
        }

        Label {
            text: qsTr("Qt version")
        }

        Label {
            text: qtVersion
        }

        Label {
            text: qsTr("Contacts")
        }

        Link {
            text: "<a href='mailto:mishkarogachev@gmail.com'>mishkarogachev@gmail.com</a>"
        }

        Label {
            text: qsTr("Web site")
        }

        Link {
            text: "<a href='https://github.com/MishkaRogachev/JAGCS'>https://github.com/MishkaRogachev/JAGCS</a>"
        }

        Label {
            text: qsTr("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.")
            Layout.columnSpan: 2
            wrapMode: Text.WordWrap
            Layout.maximumWidth: root.width - palette.margins * 2
            onWidthChanged: console.log(width)
        }
    }
}
