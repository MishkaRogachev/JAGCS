#ifndef TELEMETRY_TEST_H
#define TELEMETRY_TEST_H

#include <QTest>

class TelemetryServiceTest: public QObject
{
    Q_OBJECT

private slots:
    void testTelemetryTree();
};

#endif // TELEMETRY_TEST_H
