#include "abstract_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item.h"
#include "vehicle.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object)
{}
