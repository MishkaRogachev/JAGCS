#include "map_handle.h"

// Internal
#include "abstract_map_presenter.h"

using namespace presentation;

MapHandle::MapHandle(AbstractMapPresenter* map):
    QObject(map),
    m_map(map)
{}
