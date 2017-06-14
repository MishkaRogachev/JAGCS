#include "telemetry_test.h"

// Qt
#include <QDebug>
#include <QSignalSpy>

// Internal
#include "telemetry.h"

using namespace domain;

void TelemetryTest::testTelemetryTree()
{
    TelemetryNode root("root");
    QSignalSpy spy(&root, &TelemetryNode::parametersChanged);

    root.childNode(telemetry::satellite)->setParameter(telemetry::altitude, 666);
    root.childNode(telemetry::satellite)->setParameter(telemetry::climb, 13);

    QCOMPARE(root.takeChangedParameters().count(), 2);

    root.childNode(telemetry::satellite)->setParameter(telemetry::altitude, 665);
    root.childNode(telemetry::satellite)->setParameter(telemetry::climb, 13);
    root.childNode(telemetry::satellite)->setParameter(telemetry::fix, 2);

    QCOMPARE(root.takeChangedParameters().count(), 2);
    QCOMPARE(spy.count(), 0);

    root.childNode(telemetry::barometric)->setParameter(telemetry::altitude, 670);
    root.childNode(telemetry::satellite)->setParameter(telemetry::altitude, 669);

    root.notify();
    QCOMPARE(root.takeChangedParameters().count(), 0);
    QCOMPARE(spy.count(), 1);
}
