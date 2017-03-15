// Qt
#include <QCoreApplication>

// Internal
#include "db_manager.h"

// Tests
#include "mission_item_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    data_source::DbManager manager;
    manager.open("test_db");

    MissionItemTests missionItemTest;
    QTest::qExec(&missionItemTest);

    return 0;
}
