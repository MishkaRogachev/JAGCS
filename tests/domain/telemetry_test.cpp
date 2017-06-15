#include "telemetry_test.h"

// Qt
#include <QDebug>
#include <QSignalSpy>

// Internal
#include "telemetry.h"

using namespace domain;

void TelemetryTest::testTelemetryTree()
{
    qRegisterMetaType<TelemetryId>("TelemetryId");
    qRegisterMetaType<TelemetryList>("TelemetryList");
    qRegisterMetaType<TelemetryMap>("TelemetryMap");

    TelemetryNode root(TelemetryId::Root);
    QSignalSpy spy(&root, &TelemetryNode::parametersChanged);

    root.childNode(TelemetryId::Satellite)->setParameter(TelemetryId::Altitude, 666);
    root.childNode(TelemetryId::Satellite)->setParameter(TelemetryId::Climb, 13);

    QCOMPARE(root.childNode(TelemetryId::Satellite)->takeChangedParameters().count(), 2);

    root.childNode(TelemetryId::Satellite)->setParameter(TelemetryId::Altitude, 665);
    root.childNode(TelemetryId::Satellite)->setParameter(TelemetryId::Climb, 13);
    root.childNode(TelemetryId::Satellite)->setParameter(TelemetryId::Fix, 2);

    QCOMPARE(root.childNode(TelemetryId::Satellite)->takeChangedParameters().count(), 2);
    QCOMPARE(spy.count(), 0);

    root.childNode(TelemetryId::Barometric)->setParameter(TelemetryId::Altitude, 670);
    root.childNode(TelemetryId::Satellite)->setParameter(TelemetryId::Altitude, 669);

    root.notify();
    QCOMPARE(root.takeChangedParameters().count(), 0);
    QCOMPARE(spy.count(), 1);
}
