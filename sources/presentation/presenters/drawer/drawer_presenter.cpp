#include "drawer_presenter.h"

// Qt
#include <QUrl>
#include <QMultiMap>
#include <QDebug>

using namespace presentation;

namespace
{
    const QMultiMap<DrawerPresenter::Mode, DrawerPresenter::Mode> nestedModes
    {
        { DrawerPresenter::Home, DrawerPresenter::Planning },
        { DrawerPresenter::Home, DrawerPresenter::Vehicles },
        { DrawerPresenter::Home, DrawerPresenter::Connection },
        { DrawerPresenter::Home, DrawerPresenter::Logbook },
        { DrawerPresenter::Home, DrawerPresenter::Settings },
        { DrawerPresenter::Home, DrawerPresenter::About },
        { DrawerPresenter::Home, DrawerPresenter::Quit },

        { DrawerPresenter::Settings, DrawerPresenter::Database },
        { DrawerPresenter::Settings, DrawerPresenter::Map },
        { DrawerPresenter::Settings, DrawerPresenter::Video },
        { DrawerPresenter::Settings, DrawerPresenter::Joystick },
        { DrawerPresenter::Settings, DrawerPresenter::Gui },
        { DrawerPresenter::Settings, DrawerPresenter::Networking }
    };

    const QMap<DrawerPresenter::Mode, QString> modeStrings
    {
        { DrawerPresenter::UnknownMode, DrawerPresenter::tr("UnknownMode") },
        { DrawerPresenter::Home, DrawerPresenter::tr("Home") },
        { DrawerPresenter::Planning, DrawerPresenter::tr("Planning") },
        { DrawerPresenter::Vehicles, DrawerPresenter::tr("Vehicles") },
        { DrawerPresenter::Connection, DrawerPresenter::tr("Connection") },
        { DrawerPresenter::Logbook, DrawerPresenter::tr("Logbook") },
        { DrawerPresenter::Settings, DrawerPresenter::tr("Settings") },
        { DrawerPresenter::Database, DrawerPresenter::tr("Database") },
        { DrawerPresenter::Map, DrawerPresenter::tr("Map") },
        { DrawerPresenter::Video, DrawerPresenter::tr("Video") },
        { DrawerPresenter::Joystick, DrawerPresenter::tr("Joystick") },
        { DrawerPresenter::Gui, DrawerPresenter::tr("Gui") },
        { DrawerPresenter::Networking, DrawerPresenter::tr("Networking") },
        { DrawerPresenter::About, DrawerPresenter::tr("About") },
        { DrawerPresenter::Quit, DrawerPresenter::tr("Quit") },
    };

    const QMap<DrawerPresenter::Mode, QUrl> modeIcons
    {
        { DrawerPresenter::UnknownMode, QUrl() },
        { DrawerPresenter::Planning, QUrl("qrc:/icons/planning.svg") },
        { DrawerPresenter::Vehicles, QUrl("qrc:/icons/fleet.svg") },
        { DrawerPresenter::Connection, QUrl("qrc:/icons/connect.svg") },
        { DrawerPresenter::Logbook, QUrl("qrc:/icons/logbook.svg") },
        { DrawerPresenter::Settings, QUrl("qrc:/icons/settings.svg") },
        { DrawerPresenter::Database, QUrl("qrc:/icons/db.svg") },
        { DrawerPresenter::Map, QUrl("qrc:/icons/map.svg") },
        { DrawerPresenter::Video, QUrl("qrc:/icons/video.svg") },
        { DrawerPresenter::Joystick, QUrl("qrc:/icons/joystick.svg") },
        { DrawerPresenter::Gui, QUrl("qrc:/icons/show.svg") },
        { DrawerPresenter::Networking, QUrl("qrc:/icons/connect.svg") },
        { DrawerPresenter::About, QUrl("qrc:/icons/info.svg") },
        { DrawerPresenter::Quit, QUrl("qrc:/icons/quit.svg") },
    };

    QList<DrawerPresenter::Mode> parentModes(DrawerPresenter::Mode mode)
    {
        QList<DrawerPresenter::Mode> list;

        DrawerPresenter::Mode parentMode = nestedModes.key(mode, DrawerPresenter::UnknownMode);
        if (parentMode != DrawerPresenter::UnknownMode)
        {
            list.append(parentMode);
            list.append(parentModes(parentMode));
        }

        return list;
    }
}

DrawerPresenter::DrawerPresenter(QObject* parent):
    BasePresenter(parent)
{}

QString DrawerPresenter::modeString(Mode mode) const
{
    return ::modeStrings.value(mode);
}

QUrl DrawerPresenter::modeIcon(DrawerPresenter::Mode mode) const
{
    return ::modeIcons.value(mode);
}

void DrawerPresenter::setMode(Mode mode)
{
    QVariantList nestedModes;
    for (Mode nestedMode: ::nestedModes.values(mode))
    {
        nestedModes.prepend(QVariant::fromValue(nestedMode));
    }
    this->setViewProperty(PROPERTY(nestedModes), nestedModes);

    QVariantList parentModes;
    for (Mode parentMode: ::parentModes(mode))
    {
        parentModes.prepend(QVariant::fromValue(parentMode));
    }
    this->setViewProperty(PROPERTY(parentModes), parentModes);

    this->setViewProperty(PROPERTY(mode), QVariant::fromValue(mode));
}

void DrawerPresenter::home()
{
    this->setMode(Home);
}

