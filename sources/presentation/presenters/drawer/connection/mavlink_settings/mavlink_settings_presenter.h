#ifndef MAVLINK_SETTINGS_PRESENTER_H
#define MAVLINK_SETTINGS_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class MavLinkSettingPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MavLinkSettingPresenter(QObject* parent = nullptr);
        ~MavLinkSettingPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void setSysId(int sysId);
        void setCompId(int compId);
        void setRetranslationEnabled(bool enabled);

        void update();

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // MAVLINK_SETTINGS_PRESENTER_H
