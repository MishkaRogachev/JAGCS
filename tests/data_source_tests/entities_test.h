#ifndef ENTITIES_TEST_H
#define ENTITIES_TEST_H

#include <QTest>

class EntitiesTest: public QObject
{
    Q_OBJECT

private slots:
    void testMissionCrud();
};

#endif // ENTITIES_TEST_H
