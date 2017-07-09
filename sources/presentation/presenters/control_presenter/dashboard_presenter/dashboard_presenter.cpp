#include "dashboard_presenter.h"

// Qt
#include <QVariant>
#include <QMultiMap>

// Internal
#include "telemetry.h"

#include "base_presenter.h"

using namespace presentation;

class DashboardPresenter::Impl
{
public:
    QMap<int, QString> instruments;
    QMultiMap<QString, BasePresenter*> instrumentPresenters;
};

DashboardPresenter::DashboardPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

DashboardPresenter::~DashboardPresenter()
{
    this->setViewProperty(PROPERTY(instruments), QStringList());
}

void DashboardPresenter::addInstrument(const QString& instrument, int priority)
{
    d->instruments[priority] = instrument;
}

void DashboardPresenter::addInstrumentPresenter(const QString& instrument,
                                                BasePresenter* presenter)
{
    d->instrumentPresenters.insertMulti(instrument, presenter);
}

void DashboardPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(instrumentAdded(QString, QObject*)),
            this, SLOT(onInstrumentAdded(QString, QObject*)));

    QStringList instruments = d->instruments.values();
    this->setViewProperty(PROPERTY(instruments), instruments);
}

void DashboardPresenter::onInstrumentAdded(const QString& key, QObject* view)
{
    for (BasePresenter* instrument: d->instrumentPresenters.values(key))
    {
        instrument->setView(view);
    }
}
