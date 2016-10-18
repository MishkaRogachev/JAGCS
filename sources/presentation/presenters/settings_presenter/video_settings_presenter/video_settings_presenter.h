#ifndef VIDEO_SETTINGS_PRESENTER_H
#define VIDEO_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class VideoSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

        Q_PROPERTY(QStringList sources READ sources NOTIFY sourcesChanged)

    public:
        explicit VideoSettingsPresenter(QObject* view);
        ~VideoSettingsPresenter() override;

        QStringList sources() const;

    public slots:
        void updateSources();

    signals:
        void sourcesChanged(QStringList sources);

    private:
        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(VideoSettingsPresenter)
    };
}

#endif // VIDEO_SETTINGS_PRESENTER_H
