#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ApexSaveGame.generated.h"
USTRUCT(BlueprintType) struct FApexRaceResult { GENERATED_BODY() UPROPERTY() FName RaceId; UPROPERTY() double BestSeconds = 0.; };
UCLASS() class APEX_API UApexSaveGame : public USaveGame {
  GENERATED_BODY()
public:
  static constexpr int32 CurrentSchemaVersion = 1;
  UPROPERTY() int32 SchemaVersion = CurrentSchemaVersion;
  UPROPERTY() int64 PlayerCredits = 0;
  UPROPERTY() TArray<FName> OwnedVehicleIds;
  UPROPERTY() FName SelectedVehicleId;
  UPROPERTY() TArray<FApexRaceResult> RaceResults;
  UPROPERTY() TMap<FName, FString> Settings;
  bool Migrate();
};
