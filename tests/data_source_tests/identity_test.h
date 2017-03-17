#ifndef IDENTITY_TEST_H
#define IDENTITY_TEST_H

#include <QtTest/QTest>

class IdentityTest: public QObject
{
    Q_OBJECT

private slots:
    void testMissionIdentity();
    void testMissionItemIdentity();
};

#endif // IDENTITY_TEST_H
