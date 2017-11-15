#include "abstract_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item.h"
#include "vehicle.h"

#include "map_handle.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object),
    m_handle(new MapHandle(this))
{
    connect(m_handle, &MapHandle::missionItemSelected,
            this, &AbstractMapPresenter::selectMissionItem);
    connect(m_handle, &MapHandle::selectVehicle,
            this, &AbstractMapPresenter::selectVehicle);
}

MapHandle* AbstractMapPresenter::handle() const
{
    return m_handle;
}
