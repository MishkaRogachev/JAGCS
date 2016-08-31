#include "video_settings_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

using namespace presentation;

class VideoSettingsPresenter::Impl
{
public:
    domain::SettingsProvider* settings;

    QList<QCameraInfo> cameras;
};

VideoSettingsPresenter::VideoSettingsPresenter(
        domain::SettingsProvider* settings, QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->settings = settings;

    this->updateSources();
}

VideoSettingsPresenter::~VideoSettingsPresenter()
{
    delete d;
}

QStringList VideoSettingsPresenter::sources() const
{
    QStringList sourcesList;

    sourcesList.append(tr("none"));

    for (const QCameraInfo& info: d->cameras)
        sourcesList.append(info.deviceName());

    return sourcesList;
}

void VideoSettingsPresenter::updateSources()
{
    if (d->cameras == QCameraInfo::availableCameras()) return;
    d->cameras = QCameraInfo::availableCameras();

    emit sourcesChanged(this->sources());
}
