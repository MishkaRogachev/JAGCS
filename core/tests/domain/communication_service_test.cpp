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

using namespace data_source;
using namespace domain;

void CommunicationServiceTest::testLinkDescription()
{
     CommunicationService* service = serviceRegistry->communicationService();

     LinkDescriptionPtr description = LinkDescriptionPtr::create();
     description->setName("UDP link");
     description->setType(LinkDescription::Udp);
     description->setParameter(LinkDescription::Port, 8080);

     QVERIFY2(service->save(description), "Can't insert link");

     QVERIFY2(description->name() == "UDP link", "Link name are different");
     QCOMPARE(description->type(), LinkDescription::Udp);
     QCOMPARE(description->parameter(LinkDescription::Port).toInt(), 8080);

     QVERIFY2(service->remove(description), "Can't remove link");
}
