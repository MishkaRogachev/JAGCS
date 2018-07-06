#ifndef LINKS_TEST_H
#define LINKS_TEST_H

#include <QTest>

class LinksTest: public QObject
{
    Q_OBJECT

private slots:
    void testUdpLink();
    void testTcpLink();
};

#endif // LINKS_TEST_H
