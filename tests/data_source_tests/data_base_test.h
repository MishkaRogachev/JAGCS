#ifndef DATA_BASE_TEST_H
#define DATA_BASE_TEST_H

#include <QTest>

class DataBaseTest: public QObject
{
    Q_OBJECT

private slots:
    void testMission();
    void testMissionItems();
    void testMissionItemSequence();
    void testVehicleDescription();
    void testLinkDescription();
};

#endif // DATA_BASE_TEST_H
