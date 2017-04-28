#include "mission_item_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_item.h"

using namespace presentation;

MissionItemPresenter::MissionItemPresenter(QObject* object):
    BasePresenter(object)
{}

void MissionItemPresenter::setMissionItem(const db::MissionItemPtr& item)
{
    if (m_item == item) return;

    m_item = item;
    this->update();
}


void MissionItemPresenter::connectView(QObject* view)
{
    this->update();
}

void MissionItemPresenter::update()
{
    if (m_item)
    {
        this->setViewProperty(PROPERTY(command), m_item->command());
        this->setViewProperty(PROPERTY(altitude), m_item->altitude());
        this->setViewProperty(PROPERTY(isAltitudeRelative), m_item->isAltitudeRelative());
        this->setViewProperty(PROPERTY(latitude), m_item->latitude());
        this->setViewProperty(PROPERTY(longitude), m_item->longitude());
        this->setViewProperty(PROPERTY(radius), m_item->radius());
        this->setViewProperty(PROPERTY(pitch), m_item->pitch());
        this->setViewProperty(PROPERTY(periods), m_item->periods());
    }
    else
    {
        this->setViewProperty(PROPERTY(command), db::MissionItem::UnknownCommand);
    }
}
