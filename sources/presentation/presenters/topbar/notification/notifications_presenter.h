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
    class NotificationListModel;

    class NotificationsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit NotificationsPresenter(QObject* parent = nullptr);

    public slots:
        void addNotification(const dto::Notification& notification);

    protected:
        void connectView(QObject* view) override;

    private:
        NotificationListModel* m_model;
    };
}

#endif // NOTIFICATIONS_PRESENTER_H
