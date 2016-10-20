#ifndef VIDEO_SETTINGS_PRESENTER_H
#define VIDEO_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class VideoSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoSettingsPresenter(QObject* view);
        ~VideoSettingsPresenter() override;

    protected:
        void connectView(QObject* view) override;

    public slots:
        void updateSources();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VIDEO_SETTINGS_PRESENTER_H
