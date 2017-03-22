#ifndef DATA_BASE_TEST_H
#define DATA_BASE_TEST_H

#include <QTest>

class DataBaseTest: public QObject
{
    Q_OBJECT

private slots:
    void testMissionCrud();
    void testMissionItemCrud();
    void testMissionItemsInMission();
    void testMissionItemSequence();
    void testMissionItemUpDown();
    void testVehicleCrud();
};

#endif // DATA_BASE_TEST_H
