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
        ~PluginsPresenter() override;

    public slots:
        void discoverPlugins();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void setPlugin(const QString& plugin);
        void onRequestEnablePlugin(const QString& plugin, bool enable);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // PLUGINS_PRESENTER_H
