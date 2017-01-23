#ifndef MISSION_VIEW_HELPER_H
#define MISSION_VIEW_HELPER_H

// Qt
#include <QObject>
#include <QMap>

// Internal
#include "mission_item.h"

namespace presentation
{
    class MissionViewHelper: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionViewHelper(QObject* parent = nullptr);

        Q_INVOKABLE QStringList avalibleCommands(QObject* item) const;
        Q_INVOKABLE QString command(QObject* item) const;

    public slots:
        void setCommand(QObject* item, const QString& command);

    private:
        domain::MissionItem* cast(QObject* item) const;

        QMap<domain::MissionItem::Command, QString> m_commandNames;
    };
}

#endif // MISSION_VIEW_HELPER_H
