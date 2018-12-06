#include "mavlink_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "service_registry.h"
#include "communication_service.h"

using namespace presentation;

class MavLinkSettingPresenter::Impl
{
public:
    domain::CommunicationService* const service = serviceRegistry->communicationService();
};

MavLinkSettingPresenter::MavLinkSettingPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
}

MavLinkSettingPresenter::~MavLinkSettingPresenter()
{}

void MavLinkSettingPresenter::connectView(QObject* view)
{
    this->update();

    connect(view, SIGNAL(setSysId(int)), this, SLOT(setSysId(int)));
    connect(view, SIGNAL(setCompId(int)), this, SLOT(setCompId(int)));
    connect(view, SIGNAL(setRetranslationEnabled(bool)), this, SLOT(setRetranslationEnabled(bool)));
}

void MavLinkSettingPresenter::setSysId(int sysId)
{
    d->service->setMavLinkSysId(sysId);
    this->setViewProperty(PROPERTY(sysId), d->service->mavLinkSysId());
}

void MavLinkSettingPresenter::setCompId(int compId)
{
    d->service->setMavLinkCompId(compId);
    this->setViewProperty(PROPERTY(compId), d->service->mavLinkCompId());
}

void MavLinkSettingPresenter::setRetranslationEnabled(bool enabled)
{
    d->service->setMavLinkRetranslation(enabled);
    this->setViewProperty(PROPERTY(retranslationEnabled), d->service->mavLinkRetranslation());
}

void MavLinkSettingPresenter::update()
{
    this->setViewProperty(PROPERTY(sysId), d->service->mavLinkSysId());
    this->setViewProperty(PROPERTY(compId), d->service->mavLinkCompId());
    this->setViewProperty(PROPERTY(retranslationEnabled), d->service->mavLinkRetranslation());
}
