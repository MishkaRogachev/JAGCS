// Qt
#include <QCoreApplication>

// Tests
#include "mission_item_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    MissionItemTests missionItemTest;
    QTest::qExec(&missionItemTest);

    return app.exec();
}
