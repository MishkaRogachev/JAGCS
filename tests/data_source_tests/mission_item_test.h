#ifndef MISSION_ITEM_TEST_H
#define MISSION_ITEM_TEST_H

#include <QtTest/QTest>

class MissionItemTests : public QObject
{
    Q_OBJECT

private slots:
    void testCrud();
    //void testQueryMissionItems();
};

#endif // MISSION_ITEM_TEST_H
