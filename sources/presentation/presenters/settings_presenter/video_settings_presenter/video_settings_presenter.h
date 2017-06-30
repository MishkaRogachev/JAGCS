#ifndef VIDEO_SETTINGS_PRESENTER_H
#define VIDEO_SETTINGS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class VideoSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoSettingsPresenter(db::DbFacade* facade, QObject* parent);
        ~VideoSettingsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVideoSourceAdded(const db::VideoSourcePtr& video);
        void onVideoSourceRemoved(const db::VideoSourcePtr& video);
        void updateVideoSources();

        void onAddDeviceVideo();
        void onAddStreamVideo();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VIDEO_SETTINGS_PRESENTER_H
