#ifndef MISSION_ITEM_TEST_H
#define MISSION_ITEM_TEST_H

#include <QtTest/QTest>

class EntitiesTest : public QObject
{
    Q_OBJECT

private slots:
    void testMissionItemCrud();
    //void testQueryMissionItems();
};

#endif // MISSION_ITEM_TEST_H
