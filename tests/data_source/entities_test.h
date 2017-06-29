#ifndef ENTITIES_TEST_H
#define ENTITIES_TEST_H

#include <QTest>

class EntitiesTest: public QObject
{
    Q_OBJECT

private slots:
    void testMission();
    void testMissionItems();
    void testVehicleDescription();
    void testMissionAssignment();
    void testLinkDescription();
    void testVideoSource();
};

#endif // ENTITIES_TEST_H
