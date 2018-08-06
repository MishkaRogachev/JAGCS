#ifndef TELEMETRY_TEST_H
#define TELEMETRY_TEST_H

#include <QTest>

class TelemetryTest: public QObject
{
    Q_OBJECT

private slots:
    void testTelemetryTree();
};

#endif // TELEMETRY_TEST_H
