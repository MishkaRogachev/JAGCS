import QtQuick 2.6
import JAGCS 1.0

VideoView {
    id: video

    function updateActiveVideo() {
        presenter.updateActiveVideo();
    }

    ActiveVideoPresenter {
        id: presenter
        view: video
        Component.onCompleted: updateActiveVideo()
    }
}
