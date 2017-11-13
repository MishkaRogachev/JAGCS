#include "abstract_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "map_handle.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object),
    m_handle(new MapHandle(this))
{}

MapHandle* AbstractMapPresenter::handle() const
{
    return m_handle;
}
