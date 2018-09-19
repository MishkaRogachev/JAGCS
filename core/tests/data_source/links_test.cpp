#include "links_test.h"

// Qt
#include <QSignalSpy>
#include <QVariant>
#include <QTcpServer>
#include <QDebug>

// Internal
#include "mock_link.h"
#include "udp_link.h"
#include "tcp_link.h"

using namespace data_source;

void LinksTest::testMockLink()
{
    MockLink first, second;
    QSignalSpy firstSpy(&first, &MockLink::dataReceived);
    QSignalSpy secondSpy(&second, &MockLink::dataReceived);

    first.addLink(&second);

    QList<QByteArray> datas = { "TEST MOCK", "TEST 2 MOCK", "TEST 3 MOCK" };
    for (int i = 0; i < datas.count(); ++i)
    {
        first.sendData(datas[i]);
        QCOMPARE(secondSpy.count(), i + 1);
        QCOMPARE(second.lastReceivedData(), datas[i]);
    }
}

void LinksTest::testUdpLink()
{
    UdpLink link1(60000);
    QSignalSpy spy1(&link1, &UdpLink::dataReceived);
    QCOMPARE(link1.isConnected(), false);
    link1.connectLink();
    QCOMPARE(link1.isConnected(), true);

    UdpLink link2(60001);
    QSignalSpy spy2(&link2, &UdpLink::dataReceived);
    QCOMPARE(link2.isConnected(), false);
    link2.connectLink();
    QCOMPARE(link2.isConnected(), true);

    link1.addEndpoint(Endpoint(QHostAddress::LocalHost, 60001));

    link1.sendData("TEST UDP");

    spy2.wait();
    QCOMPARE(spy2.count(), 1);
    QList<QVariant> arguments = spy2.last();
    QCOMPARE(arguments.count(), 1);
    QCOMPARE(arguments.first(), QVariant("TEST UDP"));

    link2.sendData("AUTORESPONSE TEST");

    spy1.wait();
    QCOMPARE(spy1.count(), 1);
    arguments = spy1.last();
    QCOMPARE(arguments.count(), 1);
    QCOMPARE(arguments.first(), QVariant("AUTORESPONSE TEST"));

    link1.sendData("TEST 2 UDP");

    spy2.wait();
    QCOMPARE(spy2.count(), 3);
    arguments = spy2.last();
    QCOMPARE(arguments.count(), 1);
    QCOMPARE(arguments.first(), QVariant("TEST 2 UDP"));
}

void LinksTest::testTcpLink()
{
    QTcpServer server;
    QSignalSpy serverSpy(&server, &QTcpServer::newConnection);
    QVERIFY(server.listen(QHostAddress::LocalHost, 60000));
    QCOMPARE(serverSpy.count(), 0);
    
    TcpLink link(Endpoint(QHostAddress::LocalHost, 60000));
    QSignalSpy linkSpy(&link, &TcpLink::dataReceived);
    QCOMPARE(linkSpy.count(), 0);

    QCOMPARE(link.isConnected(), false);
    link.connectLink();
    server.waitForNewConnection(5000);
    QVERIFY(link.isConnected());
    QCOMPARE(serverSpy.count(), 1);

    QVERIFY(server.hasPendingConnections());
    QTcpSocket* socket = server.nextPendingConnection();
    QSignalSpy socketSpy(socket, &QTcpSocket::readyRead);
    QVERIFY(socket);
    QCOMPARE(socketSpy.count(), 0);

    QList<QByteArray> datas = { "TEST TCP", "TEST 2 TCP", "TEST 3 TCP" };
    for (int i = 0; i < datas.count(); ++i)
    {
        QVERIFY(socket->write(datas[i]) > 0);
        QTRY_COMPARE(linkSpy.count(), i + 1);
        QCOMPARE(link.lastReceivedData(), datas[i]);
    }
}
