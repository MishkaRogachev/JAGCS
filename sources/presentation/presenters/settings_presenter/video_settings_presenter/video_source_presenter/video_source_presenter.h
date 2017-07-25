#ifndef VIDEO_SOURCE_PRESENTER_H
#define VIDEO_SOURCE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

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
        VideoSourcePresenter(db::DbFacade* facade, const dao::VideoSourcePtr& video,
                             QObject* parent = nullptr);

        dao::VideoSourcePtr video() const;

    public slots:
        void updateView();
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void setupPreview(QObject* preview);

    private:
        db::DbFacade* const m_facade;
        dao::VideoSourcePtr m_video;
        VideoPresenter* m_preview;
    };
}

#endif // VIDEO_SOURCE_PRESENTER_H
