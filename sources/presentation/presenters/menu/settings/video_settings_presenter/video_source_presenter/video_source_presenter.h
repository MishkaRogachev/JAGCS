#ifndef VIDEO_SOURCE_PRESENTER_H
#define VIDEO_SOURCE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

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
        VideoSourcePresenter(domain::VideoService* service,
                             const dao::VideoSourcePtr& video,
                             QObject* parent = nullptr);

        dao::VideoSourcePtr video() const;

    public slots:
        void updateView();
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::VideoService* const m_service;
        dao::VideoSourcePtr m_video;
    };
}

#endif // VIDEO_SOURCE_PRESENTER_H
