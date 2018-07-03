// Qt
#include <QCoreApplication>
#include <QFile>

// Internal
#include "service_registry.h"

// Tests
#include "communication_service_test.h"
#include "telemetry_service_test.h"
#include "mission_service_test.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    {
        QFile file("test_db");
        if (file.exists()) file.remove();
    }

    domain::ServiceRegistry::instance()->init(QString("test_db"));

    CommunicationServiceTest commTest;
    QTest::qExec(&commTest);

    TelemetryServiceTest telemetryTest;
    QTest::qExec(&telemetryTest);

    MissionServiceTest missionTest;
    QTest::qExec(&missionTest);

    return 0;
}
