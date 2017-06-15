#include "telemetry_test.h"

// Qt
#include <QDebug>
#include <QSignalSpy>

// Internal
#include "telemetry.h"

using namespace domain;

void TelemetryTest::testTelemetryTree()
{
    //qRegisterMetaType<Telemetry::TelemetryId>("TelemetryId");
    qRegisterMetaType<Telemetry::TelemetryList>("TelemetryList");
    qRegisterMetaType<Telemetry::TelemetryMap>("TelemetryMap");

    Telemetry root(Telemetry::Root);
    QSignalSpy spy(&root, &Telemetry::parametersChanged);

    root.childNode(Telemetry::Satellite)->setParameter(Telemetry::Altitude, 666);
    root.childNode(Telemetry::Satellite)->setParameter(Telemetry::Climb, 13);

    QCOMPARE(root.childNode(Telemetry::Satellite)->takeChangedParameters().count(), 2);

    root.childNode(Telemetry::Satellite)->setParameter(Telemetry::Altitude, 665);
    root.childNode(Telemetry::Satellite)->setParameter(Telemetry::Climb, 13);
    root.childNode(Telemetry::Satellite)->setParameter(Telemetry::Fix, 2);

    QCOMPARE(root.childNode(Telemetry::Satellite)->takeChangedParameters().count(), 2);
    QCOMPARE(spy.count(), 0);

    root.childNode(Telemetry::Barometric)->setParameter(Telemetry::Altitude, 670);
    root.childNode(Telemetry::Satellite)->setParameter(Telemetry::Altitude, 669);

    root.notify();
    QCOMPARE(root.takeChangedParameters().count(), 0);
    QCOMPARE(spy.count(), 1);
}
