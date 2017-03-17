#ifndef REPOSITORIES_TEST_H
#define REPOSITORIES_TEST_H

#include <QtTest/QTest>

class RepositoriesTest: public QObject
{
    Q_OBJECT

private slots:
    void testMissionItemCrud();
    void testSelectMissionItems();
    void testMissionCrud();
    void testSelectMissions();
};

#endif // REPOSITORIES_TEST_H
