#ifndef DB_MIGRATOR_H
#define DB_MIGRATOR_H

// Qt
#include <QObject>
#include <QDateTime>

// Internal
#include "db_traits.h"

namespace data_source
{
    class DbMigrator: public QObject
    {
        Q_OBJECT

    public:
        explicit DbMigrator(QObject* parent = nullptr);

        bool migrate(const QDateTime& version = QDateTime::currentDateTime());
        bool drop();
        bool clarifyVersion();

        void reset();

        QDateTime version() const;

    signals:
        void versionChanged(QDateTime version);
        void message(const QString& message);

    private slots:
        void setVersion(const QDateTime& version);

    private:
        DbMigrationPtrList m_migrations;
        QDateTime m_version;
    };
}

#endif // DB_MIGRATOR_H
