#ifndef VIDEO_SOURCE_PRESENTER_H
#define VIDEO_SOURCE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class VideoPresenter;

    class VideoSourcePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VideoSourcePresenter(db::DbFacade* facade, const db::VideoSourcePtr& video,
                             QObject* parent = nullptr);

        db::VideoSourcePtr video() const;

    public slots:
        void restore();
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        db::DbFacade* const m_facade;
        db::VideoSourcePtr m_video;
        VideoPresenter* m_preview;
    };
}

#endif // VIDEO_SOURCE_PRESENTER_H
