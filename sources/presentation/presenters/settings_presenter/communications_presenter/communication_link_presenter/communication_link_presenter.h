#ifndef COMMUNICATION_LINK_PRESENTER_H
#define COMMUNICATION_LINK_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class CommunicationManager;
}

namespace presentation
{
    class CommunicationLinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationLinkPresenter(domain::CommunicationManager* manager,
                                   const data_source::LinkDescriptionPtr& description,
                                   QObject* parent = nullptr);

        data_source::LinkDescriptionPtr description() const;

    public slots:
        void updateView();
        void updateStatistics(int sentBytes, int recvBytes);

    signals:
        void setConnected(bool connected);

    protected:
        void connectView(QObject* view) override;
        void setViewSignalsEnbled(bool enabled);

    private slots:
        void onSetName(const QString& name);
        void onSetPort(int port);
        void onSetDevice(const QString& device);
        void onSetBaudRate(int rate);
        void onSetConnected(bool connected);
        void onRemove();

    private:
        domain::CommunicationManager* const m_manager;
        data_source::LinkDescriptionPtr m_description;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
