#ifndef ENTITIES_TEST_H
#define ENTITIES_TEST_H

#include <QTest>

class EntitiesTest: public QObject
{
    Q_OBJECT

private slots:
    void testMissionCrud();
    void testMissionItemCrud();
    void testMissionItemsInMission();
    void testMissionItemSequence();
    void testMissionItemUpDown();
};

#endif // ENTITIES_TEST_H
