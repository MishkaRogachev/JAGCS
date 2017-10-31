import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

ColumnLayout {
    id: root

    property string version: qsTr("(undefined version)")
    property string revision: qsTr("Undefined")
    property string qtVersion: qsTr("Undefined")

    spacing: palette.spacing

    Flickable {
        Layout.fillWidth: true
        Layout.fillHeight: true
        contentHeight: frame.height
        clip: true

        ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            id: frame
            width: root.width

            GridLayout {
                id: grid
                columns: 2
                rowSpacing: palette.spacing
                columnSpacing: palette.spacing

                Controls.Label {
                    text: "Just another ground control station " + version
                    font.bold: true
                    Layout.columnSpan: 2
                }

                Controls.Label {
                    text: qsTr("Revision")
                }

                Controls.Label {
                    text: revision
                }

                Controls.Label {
                    text: qsTr("Qt version")
                }

                Controls.Label {
                    text: qtVersion
                }

                Controls.Label {
                    text: qsTr("Contacts")
                }

                Controls.Link {
                    text: "<a href='mailto:mishkarogachev@gmail.com'>mishkarogachev@gmail.com</a>"
                }

                Controls.Label {
                    text: qsTr("Web site")
                }

                Controls.Link {
                    text: "<a href='https://github.com/MishkaRogachev/JAGCS'>https://github.com/MishkaRogachev/JAGCS</a>"
                }

                Controls.Label {
                    text: qsTr("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.")
                    Layout.columnSpan: 2
                    wrapMode: Text.WordWrap
                    Layout.maximumWidth: root.parent.width - palette.margins * 2
                }
            }
        }
    }
}
