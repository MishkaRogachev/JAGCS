import QtQuick 2.6
import JAGCS 1.0

VideoView {
    id: video

    VideoPresenter {
        view: video
    }
}
