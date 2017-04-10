#ifndef COMMUNICATION_LINK_PRESENTER_H
#define COMMUNICATION_LINK_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace presentation
{
    class CommunicationLinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationLinkPresenter(const data_source::LinkDescriptionPtr& description,
                                   QObject* parent = nullptr);

        data_source::LinkDescriptionPtr description() const;

    public slots:
        void updateView();

    signals:
        void remove();

    protected:
        void connectView(QObject* view) override;
        void setViewSignalsEnbled(bool enabled);

    private slots:
        void onSetType(const QString& type);
        void onSetName(const QString& name);
        void onSetPort(int port);
        void onSetDevice(const QString& device);
        void onSetBaudRate(int rate);

    private:
        data_source::LinkDescriptionPtr m_description;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
