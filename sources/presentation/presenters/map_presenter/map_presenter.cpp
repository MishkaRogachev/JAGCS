#include "map_presenter.h"

using namespace presentation;

MapPresenter::MapPresenter(QObject* parent):
    BasePresenter(parent)
{}

void MapPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)
}
