#include "entities_test.h"

// Qt
#include <QDebug>

// Internal
#include "identity_map.h"

#include "mission.h"

using namespace data_source;

void EntitiesTest::testMissionCrud()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();

    QVERIFY(mission);

    mission->setName("Some ridiculous name");
    iMap.saveMission(mission);
}
