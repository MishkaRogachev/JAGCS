#ifndef MAP_SETTINGS_PRESENTER_H
#define MAP_SETTINGS_PRESENTER_H

#include "base_presenter.h"

namespace presentation
{
    class MapSettingsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MapSettingsPresenter(QObject* parent);

    public slots:
        void updateView();
        void save();

    protected:
        void connectView(QObject* view) override;
    };
}

#endif // MAP_SETTINGS_PRESENTER_H
