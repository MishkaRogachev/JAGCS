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

    private slots:
        void onLogAdded(const dto::Notification& message);
    };
}

#endif // NOTIFICATIONS_PRESENTER_H
