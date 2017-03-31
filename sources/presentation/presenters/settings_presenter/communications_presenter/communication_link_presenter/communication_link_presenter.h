#ifndef COMMUNICATION_LINK_PRESENTER_H
#define COMMUNICATION_LINK_PRESENTER_H

#include "base_presenter.h"

namespace data_source
{
    class LinkDescription;
}

namespace presentation
{
    class CommunicationLinkPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        CommunicationLinkPresenter(data_source::LinkDescription* description,
                                   QObject* parent = nullptr);

        data_source::LinkDescription* description() const;

    public slots:
        void updateView();

    signals:
        void remove();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSetType(const QString& type);
        void onSetName(const QString& name);
        void onSetPort(int port);
        void onSetDevice(const QString& device);
        void onSetBaudRate(int rate);

    private:
        data_source::LinkDescription* m_description;
    };
}

#endif // COMMUNICATION_LINK_PRESENTER_H
