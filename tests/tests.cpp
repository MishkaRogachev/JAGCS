// Qt
#include <QCoreApplication>
#include <QFile>

// Internal
#include "db_manager.h"

// Tests
#include "entities_test.h"
#include "links_test.h"
#include "telemetry_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    {
        QFile file("test_db");
        if (file.exists()) file.remove();
    }

    db::DbManager manager;

    manager.open("test_db");

    EntitiesTest entitiesTest;
    QTest::qExec(&entitiesTest);

    LinksTest linksTest;
    QTest::qExec(&linksTest);

    TelemetryTest telemetryTest;
    QTest::qExec(&telemetryTest);

    manager.drop();

    return 0;
}
