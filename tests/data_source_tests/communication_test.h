#ifndef COMMUNICATION_TEST_H
#define COMMUNICATION_TEST_H

#include <QTest>

class CommunicationTest: public QObject
{
    Q_OBJECT

private slots:
    // TODO: endpoints tests
    void testUdpLink();
};

#endif // COMMUNICATION_TEST_H
