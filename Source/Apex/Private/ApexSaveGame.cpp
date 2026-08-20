#include "ApexSaveGame.h"
bool UApexSaveGame::Migrate() { if (SchemaVersion < 1) SchemaVersion = 1; return SchemaVersion == CurrentSchemaVersion; }
