#ifndef DB_FACADE_H
#define DB_FACADE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace db
{
    // TODO: work with db in separated thread
    class DbFacade: public QObject
    {
        Q_OBJECT

    public:
        explicit DbFacade(QObject* parent = nullptr);
        ~DbFacade() override;

        dao::VideoSourcePtr videoSource(int id, bool reload = false);

        bool save(const dao::VideoSourcePtr& videoSource);
        bool remove(const dao::VideoSourcePtr& videoSource);

        dao::VideoSourcePtrList videoSources(const QString& condition = QString(),
                                             bool reload  = false);

    signals:
        void videoSourceAdded(dao::VideoSourcePtr videoSource);
        void videoSourceRemoved(dao::VideoSourcePtr videoSource);
        void videoSourceChanged(dao::VideoSourcePtr videoSource);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DB_FACADE_H
