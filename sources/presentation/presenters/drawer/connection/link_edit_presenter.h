#ifndef LINK_EDIT_PRESENTER_H
#define LINK_EDIT_PRESENTER_H

// Internal
#include "link_presenter.h"

namespace domain
{
    class SerialPortService;
    class BluetoothService;
}

namespace presentation
{
    class LinkStatisticsModel;

    class LinkEditPresenter: public LinkPresenter
    {
        Q_OBJECT

    public:
        explicit LinkEditPresenter(QObject* parent = nullptr);

        Q_INVOKABLE QString bluetoothAddress(const QString& device) const;

    public slots:
        void setLink(int id) override;
        void updateLink() override;
        void updateRates();
        void updateDevices();
        void startBluetoothDiscovery();
        void stopBluetoothDiscovery();
        void save();

    protected:
        void connectView(QObject* view) override;

    protected slots:
        void updateStatistics(const dto::LinkStatisticsPtr& statistics) override;

    private:
        domain::SerialPortService* const m_serialService;
        domain::BluetoothService* const m_bluetoothService;

        LinkStatisticsModel* const m_statisticsModel;
    };
}

#endif // LINK_EDIT_PRESENTER_H
