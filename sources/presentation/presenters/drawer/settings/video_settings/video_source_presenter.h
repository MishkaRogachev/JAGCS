#ifndef VIDEO_SOURCE_PRESENTER_H
#define VIDEO_SOURCE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

namespace domain
{
    class VideoService;
}

namespace presentation
{
    class VideoSourcePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoSourcePresenter(QObject* parent = nullptr);

    public slots:
        void setVideo(int id);
        void updateLink();

        void setSource(const QString& source);
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::VideoService* const m_service;
        dto::VideoSourcePtr m_video;
    };
}

#endif // VIDEO_SOURCE_PRESENTER_H
