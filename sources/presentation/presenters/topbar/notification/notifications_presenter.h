#ifndef NOTIFICATIONS_PRESENTER_H
#define NOTIFICATIONS_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace dto
{
    class Notification;
}

namespace presentation
{
    class NotificationsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit NotificationsPresenter(QObject* parent = nullptr);
        ~NotificationsPresenter() override;

    public slots:
        void addNotification(const dto::Notification& notification);

        void remove(const QString& header);
        void removeLast();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // NOTIFICATIONS_PRESENTER_H
