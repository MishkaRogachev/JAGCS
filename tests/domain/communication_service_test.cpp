#include "communication_service_test.h"

// Qt
#include <QSignalSpy>
#include <QVariant>
#include <QDebug>

// Internal
#include "udp_link.h"
#include "serial_link.h"

#include "service_registry.h"
#include "communication_service.h"
#include "link_description.h"

using namespace dao; // TODO: dao tests
using namespace comm;
using namespace domain;

void CommunicationServiceTest::testUdpLink()
{
    UdpLink link1(60000);
    QSignalSpy spy1(&link1, SIGNAL(dataReceived(QByteArray)));
    link1.connectLink();

    UdpLink link2(60001);
    QSignalSpy spy2(&link2, SIGNAL(dataReceived(QByteArray)));
    link2.connectLink();

    link1.addEndpoint(Endpoint(QHostAddress::LocalHost, 60001));

    link1.sendData("TEST");

    spy2.wait();
    QCOMPARE(spy2.count(), 1);
    QList<QVariant> arguments = spy2.last();
    QCOMPARE(arguments.count(), 1);
    QCOMPARE(arguments.first(), QVariant("TEST"));

    link2.sendData("AUTORESPONSE TEST");

    spy1.wait();
    QCOMPARE(spy1.count(), 1);
    arguments = spy1.last();
    QCOMPARE(arguments.count(), 1);
    QCOMPARE(arguments.first(), QVariant("AUTORESPONSE TEST"));

    link1.sendData("TEST 2");

    spy2.wait();
    QCOMPARE(spy2.count(), 3);
    arguments = spy2.last();
    QCOMPARE(arguments.count(), 1);
    QCOMPARE(arguments.first(), QVariant("TEST 2"));
}

void CommunicationServiceTest::testLinkDescription()
{
     CommunicationService* service = ServiceRegistry::communicationService();

     LinkDescriptionPtr description = LinkDescriptionPtr::create();
     description->setName("UDP link");
     description->setType(LinkDescription::Udp);
     description->setPort(8080);

     QVERIFY2(service->save(description), "Can't insert link");
     service->description(description->id(), true);

     QVERIFY2(description->name() == "UDP link", "Link name are different");
     QCOMPARE(description->type(), LinkDescription::Udp);
     QCOMPARE(description->port(), 8080);

     QVERIFY2(service->remove(description), "Can't remove link");
}
