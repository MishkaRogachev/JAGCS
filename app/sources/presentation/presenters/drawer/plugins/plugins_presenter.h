#ifndef PLUGINS_PRESENTER_H
#define PLUGINS_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class PluginsPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit PluginsPresenter(QObject* parent = nullptr);

    public slots:
        void updatePlugins();
        void discoverPlugins();
    };
}

#endif // PLUGINS_PRESENTER_H
