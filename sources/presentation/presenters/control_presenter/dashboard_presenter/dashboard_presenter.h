#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

// Qt
#include <QMap>

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
        void addInstrument(const QString& viewName, AbstractInstrumentPresenter* instrument);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onInstrumentAdded(const QString& key, QObject* view);

    private:
        QMap<QString, AbstractInstrumentPresenter*> m_instruments;
    };
}

#endif // DASHBOARD_PRESENTER_H
