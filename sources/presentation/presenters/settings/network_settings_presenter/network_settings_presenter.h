#ifndef NETWORK_SETTINGS_PRESENTER_H
#define NETWORK_SETTINGS_PRESENTER_H

#include <QObject>

namespace presentation
{
    class NetworkSettingsPresenter: public QObject
    {
        Q_OBJECT

    public:
        explicit NetworkSettingsPresenter(QObject* parent = nullptr);

    public slots:
        void restore();
        void apply();
    };
}

#endif // NETWORK_SETTINGS_PRESENTER_H
