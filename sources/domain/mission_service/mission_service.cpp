#include "mission_service.h"

using namespace db;
using namespace domain;

class MissionService::Impl
{
public:
    DbEntry* entry;
};

MissionService::MissionService(db::DbEntry* entry, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->entry = entry;
}

MissionService::~MissionService()
{}
