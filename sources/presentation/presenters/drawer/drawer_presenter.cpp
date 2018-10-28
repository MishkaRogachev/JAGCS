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
        { DrawerPresenter::Home, DrawerPresenter::Plan },
        { DrawerPresenter::Home, DrawerPresenter::Fleet },
        { DrawerPresenter::Home, DrawerPresenter::Connection },
        { DrawerPresenter::Home, DrawerPresenter::Logs },
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

    const QMap<DrawerPresenter::Mode, QUrl> modeIcons
    {
        { DrawerPresenter::UnknownMode, QUrl() },
        { DrawerPresenter::Plan, QUrl("qrc:/icons/planning.svg") },
        { DrawerPresenter::Fleet, QUrl("qrc:/icons/fleet.svg") },
        { DrawerPresenter::Connection, QUrl("qrc:/icons/connect.svg") },
        { DrawerPresenter::Logs, QUrl("qrc:/icons/logbook.svg") },
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
    static const QMap<DrawerPresenter::Mode, QString> modeStrings
    {
        { DrawerPresenter::UnknownMode, tr("UnknownMode") },
        { DrawerPresenter::Home, tr("Home") },
        { DrawerPresenter::Plan, tr("Plan") },
        { DrawerPresenter::Fleet, tr("Fleet") },
        { DrawerPresenter::Connection, tr("Connection") },
        { DrawerPresenter::Logs, tr("Logs") },
        { DrawerPresenter::Settings, tr("Settings") },
        { DrawerPresenter::Database, tr("Database") },
        { DrawerPresenter::Map, tr("Map") },
        { DrawerPresenter::Video, tr("Video") },
        { DrawerPresenter::Joystick, tr("Joystick") },
        { DrawerPresenter::Gui, tr("Gui") },
        { DrawerPresenter::Networking, tr("Networking") },
        { DrawerPresenter::About, tr("About") },
        { DrawerPresenter::Quit, tr("Quit") },
    };

    return modeStrings.value(mode);
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

