#ifndef VIDEO_SETTINGS_PRESENTER_H
#define VIDEO_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class SettingsProvider;
}

namespace presentation
{
    class VideoSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

        Q_PROPERTY(QStringList sources READ sources NOTIFY sourcesChanged)

    public:
        VideoSettingsPresenter(domain::SettingsProvider* settings, QObject* view);
        ~VideoSettingsPresenter() override;

        QStringList sources() const;

    public slots:
        void updateSources();

    signals:
        void sourcesChanged(QStringList sources);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VIDEO_SETTINGS_PRESENTER_H
