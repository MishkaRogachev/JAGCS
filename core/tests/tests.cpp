// Qt
#include <QCoreApplication>

// Core
#include "db_manager.h"
#include "notification_bus.h"
#include "service_registry.h"

// Tests
#include "links_test.h"
#include "serial_device_pool_test.h"
#include "telemetry_test.h"

#include "communication_service_test.h"
#include "mission_service_test.h"

#define execTest(T) { T t; QTest::qExec(&t); }

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    execTest(LinksTest)
    execTest(SerialDevicePoolTest)
    execTest(TelemetryTest)

    /*{
        QFile file("test_db");
        if (file.exists()) file.remove();
    }

    {
        domain::DbManager manager;
        if (!manager.open("test_db"))
        {
            qFatal("Unable to establish DB connection");
            app.quit();
        }

        domain::ServiceRegistry registy;
        Q_UNUSED(registy);

        execTest(CommunicationServiceTest)
        execTest(MissionServiceTest)
    }*/

    return 0;
}
