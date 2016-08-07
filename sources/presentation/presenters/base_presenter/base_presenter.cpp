#include "base_presenter.h"

using namespace presentation;

BasePresenter::BasePresenter(QObject* view):
    BasePresenter(view, view)
{}

BasePresenter::BasePresenter(QObject* view, QObject* parent):
    QObject(parent),
    m_view(view)
{
    Q_ASSERT(view);
}

void BasePresenter::setViewProperty(const char* name, const QVariant& value)
{
    m_view->setProperty(name, value);
}

void BasePresenter::invokeViewMethod(const char* name, const QVariant& value)
{
    QMetaObject::invokeMethod(m_view, name, Q_ARG(QVariant, value));
}

