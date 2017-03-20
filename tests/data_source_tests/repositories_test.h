#ifndef REPOSITORIES_TEST_H
#define REPOSITORIES_TEST_H

#include <QtTest/QTest>

class RepositoriesTest: public QObject
{
    Q_OBJECT

private slots:
    void testMissionCrud();
    void testSelectMissions();
    void testMissionItemCrud();
    void testSelectMissionItems();
};

#endif // REPOSITORIES_TEST_H
