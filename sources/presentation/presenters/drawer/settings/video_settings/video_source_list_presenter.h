#ifndef VIDEO_SOURCE_LIST_PRESENTER_H
#define VIDEO_SOURCE_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

namespace domain
{
    class VideoService;
}

namespace presentation
{
    class VideoSourceListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoSourceListPresenter(QObject* parent = nullptr);
        ~VideoSourceListPresenter() override;

    public slots:
        void updateCameraInfo();

        void addDeviceVideo();
        void addStreamVideo();
        void saveActiveVideo(int video);

        void filter(const QString& filterString);

    protected:
        void connectView(QObject* view) override;

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // VIDEO_SOURCE_LIST_PRESENTER_H
