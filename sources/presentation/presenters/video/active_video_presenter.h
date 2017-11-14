#ifndef VIDEO_SPLIT_PRESENTER_H
#define VIDEO_SPLIT_PRESENTER_H

#include "video_presenter.h"

namespace presentation
{
    class ActiveVideoPresenter: public VideoPresenter
    {
        Q_OBJECT

    public:
        ActiveVideoPresenter(QObject* parent = nullptr);

    public slots:
        void updateActiveVideo();

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // VIDEO_SPLIT_PRESENTER_H
