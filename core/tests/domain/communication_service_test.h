#ifndef COMMUNICATION_SERVICE_TEST_H
#define COMMUNICATION_SERVICE_TEST_H

#include <QTest>

class CommunicationServiceTest: public QObject
{
    Q_OBJECT

private slots:
    // TODO: endpoints tests
    void testUdpLink();
    void testLinkDescription();
};

#endif // COMMUNICATION_SERVICE_TEST_H
