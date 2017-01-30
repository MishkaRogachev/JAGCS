#include "base_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

using namespace presentation;

BasePresenter::BasePresenter(QObject* parent):
    QObject(parent),
    m_view(nullptr)
{}

QObject* BasePresenter::view() const
{
    return m_view;
}

void BasePresenter::setView(QObject* view)
{
    if (m_view) this->disconnectView(m_view);

    m_view = view;

    if (view) this->connectView(view);
}

QVariant BasePresenter::viewProperty(const char* name) const
{
    return m_view->property(name);
}

void BasePresenter::connectView(QObject* view)
{
    Q_UNUSED(view)
}

void BasePresenter::disconnectView(QObject* view)
{
    disconnect(view, 0, this, 0);
    disconnect(this, 0, view, 0);
}

void BasePresenter::setViewProperty(const char* name, const QVariant& value)
{
    m_view->setProperty(name, value);
}

void BasePresenter::invokeViewMethod(const char* name)
{
    QMetaObject::invokeMethod(m_view, name);
}

void BasePresenter::invokeViewMethod(const char* name, const QVariant& value)
{
    QMetaObject::invokeMethod(m_view, name, Q_ARG(QVariant, value));
}

