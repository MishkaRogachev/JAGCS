#ifndef VIDEO_SPLIT_PRESENTER_H
#define VIDEO_SPLIT_PRESENTER_H

#include "base_presenter.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class VideoPresenter;

    class VideoSplitPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VideoSplitPresenter(db::DbFacade* dbFacade, QObject* parent = nullptr);

    public slots:
        void updateSources();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSelectVideoSource(int index);

    private:
        db::DbFacade* m_dbFacade;
        VideoPresenter* m_video;
    };
}

#endif // VIDEO_SPLIT_PRESENTER_H
