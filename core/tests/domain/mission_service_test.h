#ifndef TELEMETRY_SERVICE_TEST_H
#define TELEMETRY_SERVICE_TEST_H

#include <QTest>

class MissionServiceTest: public QObject
{
    Q_OBJECT

private slots:
    void testMission();
    void testMissionItems();
    void testVehicleDescription();
    void testMissionAssignment();
};

#endif // TELEMETRY_SERVICE_TEST_H
