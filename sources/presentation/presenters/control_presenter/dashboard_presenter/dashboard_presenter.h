#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class DashboardPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DashboardPresenter(QObject* parent = nullptr);
        ~DashboardPresenter() override;

    public slots:
        void addInstrument(const QString& instrument, BasePresenter* presenter);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onInstrumentAdded(const QString& key, QObject* view);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DASHBOARD_PRESENTER_H
