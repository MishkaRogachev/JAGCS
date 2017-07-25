#ifndef CONTROL_PRESENTER_H
#define CONTROL_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class ControlPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit ControlPresenter(domain::DomainEntry* entry, QObject* parent = nullptr);
        ~ControlPresenter() override;

    public slots:
        void updateVehiclesList();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSelectVehicle(int index);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // CONTROL_PRESENTER_H
