#ifndef ABOUT_PRESENTER_H
#define ABOUT_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class AboutPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit AboutPresenter(QObject* parent = nullptr);

    public slots:
        void updateVersions();
    };
}

#endif // ABOUT_PRESENTER_H
