import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import Industrial.Controls 1.0 as Controls

Flickable {
    id: about

    property string version: qsTr("(undefined version)")
    property string revision: qsTr("Undefined")
    property string qtVersion: qsTr("Undefined")

    implicitWidth: contents.implicitWidth
    contentHeight: contents.height
    boundsBehavior: Flickable.OvershootBounds
    flickableDirection: Flickable.AutoFlickIfNeeded

    Controls.ScrollBar.vertical: Controls.ScrollBar {}

    AboutPresenter {
        view: about
        Component.onCompleted: updateVersions()
    }

    GridLayout {
        id: contents
        width: parent.width
        columns: 2
        rowSpacing: industrial.spacing
        columnSpacing: industrial.spacing

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
            text: qsTr("Donate")
        }

        Controls.Link {
            text: "<a href='https://www.paypal.me/MishkaRogachev'>https://www.paypal.me/MishkaRogachev</a>"
        }

        Controls.Label {
            text: qsTr("THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.")
            Layout.columnSpan: 2
            wrapMode: Text.WordWrap
            Layout.maximumWidth: about.width - industrial.margins * 2
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
