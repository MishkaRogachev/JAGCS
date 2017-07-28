#ifndef VIDEO_SPLIT_PRESENTER_H
#define VIDEO_SPLIT_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class VideoService;
}

namespace presentation
{
    class VideoPresenter;

    class VideoSplitPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VideoSplitPresenter(QObject* parent = nullptr);

    public slots:
        void updateSources();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSelectVideoSource(int index);

    private:
        domain::VideoService* m_videoService;
        VideoPresenter* m_video;
    };
}

#endif // VIDEO_SPLIT_PRESENTER_H
