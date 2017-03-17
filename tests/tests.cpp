// Qt
#include <QCoreApplication>

// Internal
#include "db_manager.h"

// Tests
#include "entities_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    data_source::DbManager manager;

    manager.open("test_db");
    manager.create();

    EntitiesTest entitiesTest;
    QTest::qExec(&entitiesTest);

    manager.drop();

    return 0;
}
