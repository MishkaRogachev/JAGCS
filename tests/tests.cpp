// Qt
#include <QCoreApplication>

// Internal
#include "db_manager.h"

// Tests
#include "repositories_test.h"
#include "identity_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    data_source::DbManager manager;

    manager.open("test_db");
    manager.create();

    RepositoriesTest repositoriesTest;
    QTest::qExec(&repositoriesTest);

    IdentityTest identityTest;
    QTest::qExec(&identityTest);

    manager.drop();

    return 0;
}
