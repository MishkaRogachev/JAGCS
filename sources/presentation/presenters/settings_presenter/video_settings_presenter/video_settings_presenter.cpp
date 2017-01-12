#include "video_settings_presenter.h"

// Qt
#include <QCameraInfo>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;

class VideoSettingsPresenter::Impl
{
public:
    QList<QCameraInfo> cameras;
};

VideoSettingsPresenter::VideoSettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

VideoSettingsPresenter::~VideoSettingsPresenter()
{
    delete d;
}

void VideoSettingsPresenter::connectView(QObject* view)
{
    this->updateSources();

    connect(view, SIGNAL(sourceSelected(QString)),
            this, SLOT(onSourceSelected(QString)));
}

void VideoSettingsPresenter::onSourceSelected(const QString& source)
{
    domain::SettingsProvider::beginGroup(domain::video_settings::group);
    domain::SettingsProvider::setValue(domain::video_settings::device, source);
    domain::SettingsProvider::endGroup();
}

void VideoSettingsPresenter::updateSources()
{
    d->cameras = QCameraInfo::availableCameras();

    QStringList sourcesList;

    sourcesList.append(tr("none"));

    for (const QCameraInfo& info: d->cameras)
        sourcesList.append(info.deviceName());

    this->setViewProperty(PROPERTY(sourcesModel), sourcesList);

    this->updateCurrentSource();
}

void VideoSettingsPresenter::updateCurrentSource()
{
    domain::SettingsProvider::beginGroup(domain::video_settings::group);

    this->invokeViewMethod(PROPERTY(setSource),
                           domain::SettingsProvider::value(
                               domain::video_settings::device));

    domain::SettingsProvider::endGroup();
}
