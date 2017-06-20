#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class AbstractInstrumentPresenter;

    class DashboardPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DashboardPresenter(QObject* parent = nullptr);
        ~DashboardPresenter() override;

    public slots:
        void addInstrument(const QString& instrument,
                           AbstractInstrumentPresenter* presenter);

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
