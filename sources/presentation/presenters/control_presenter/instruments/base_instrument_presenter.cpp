#include "base_instrument_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

BaseInstrumentPresenter::BaseInstrumentPresenter(QObject* parent):
    QObject(parent)
{}

void BaseInstrumentPresenter::addInstrumentView(QObject* view)
{
    m_views.append(view);
    this->connectView(view);
}

void BaseInstrumentPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)
}

void BaseInstrumentPresenter::setViewsProperty(const char* name, const QVariant& value)
{
    for (QObject* view: m_views)
    {
        if (view->property(name).isValid()) view->setProperty(name, value);
    }
}
