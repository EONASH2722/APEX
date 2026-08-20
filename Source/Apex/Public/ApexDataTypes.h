#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ApexDataTypes.generated.h"

UENUM(BlueprintType) enum class EApexDataConfidence : uint8 { Unknown, EngineeringEstimate, SecondarySource, Manufacturer };
UENUM(BlueprintType) enum class EApexDrivetrain : uint8 { FWD, RWD, AWD };
UENUM(BlueprintType) enum class EApexRaceType : uint8 { PointToPoint, Lap };

USTRUCT(BlueprintType) struct FApexSourceMetadata {
  GENERATED_BODY()
  UPROPERTY(EditAnywhere) FString Unit;
  UPROPERTY(EditAnywhere) FString SourceUrl;
  UPROPERTY(EditAnywhere) FString SourceName;
  UPROPERTY(EditAnywhere) EApexDataConfidence Confidence = EApexDataConfidence::Unknown;
  UPROPERTY(EditAnywhere) FString Notes;
  UPROPERTY(EditAnywhere) int32 ModelYear = 0;
  UPROPERTY(EditAnywhere) FString Trim;
};
USTRUCT(BlueprintType) struct FApexSourcedFloat {
  GENERATED_BODY()
  UPROPERTY(EditAnywhere) bool bHasValue = false;
  UPROPERTY(EditAnywhere) double Value = 0.;
  UPROPERTY(EditAnywhere) FApexSourceMetadata Source;
};
USTRUCT(BlueprintType) struct FApexTorquePoint { GENERATED_BODY() UPROPERTY(EditAnywhere) float RPM = 0.f; UPROPERTY(EditAnywhere) float TorqueNm = 0.f; };
USTRUCT(BlueprintType) struct FApexPerformanceTargets {
  GENERATED_BODY()
  UPROPERTY(EditAnywhere) FApexSourcedFloat ZeroTo100Seconds;
  UPROPERTY(EditAnywhere) FApexSourcedFloat ZeroTo200Seconds;
  UPROPERTY(EditAnywhere) FApexSourcedFloat QuarterMileSeconds;
  UPROPERTY(EditAnywhere) FApexSourcedFloat TopSpeedKmh;
  UPROPERTY(EditAnywhere) FApexSourcedFloat Braking100To0Meters;
};
UCLASS(BlueprintType) class APEX_API UApexVehicleSpecification : public UPrimaryDataAsset {
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FPrimaryAssetType AssetType = TEXT("VehicleSpecification");
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FName VehicleId;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FApexSourcedFloat MassKg;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FApexSourcedFloat WheelbaseM;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FApexSourcedFloat FrontTrackM;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FApexSourcedFloat RearTrackM;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FApexTorquePoint> TorqueCurve;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float IdleRPM = 800.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float RedlineRPM = 7000.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<float> ForwardGearRatios;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float FinalDriveRatio = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) EApexDrivetrain Drivetrain = EApexDrivetrain::RWD;
  UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin="0", ClampMax="1")) float DrivetrainEfficiency = .85f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float DragCoefficient = .3f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float FrontalAreaM2 = 2.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float LiftCoefficient = 0.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FApexPerformanceTargets ValidationTargets;
  virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(AssetType, VehicleId); }
};

UCLASS(BlueprintType) class APEX_API UApexSurfaceProfile : public UPrimaryDataAsset {
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FName SurfaceId;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float FrictionCoefficient = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float RollingResistance = .015f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float LongitudinalGripMultiplier = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) float LateralGripMultiplier = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<UObject> TireAudio;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) TSoftObjectPtr<UObject> TireParticles;
};

USTRUCT(BlueprintType) struct FApexCheckpointDefinition { GENERATED_BODY() UPROPERTY(EditAnywhere) FGuid Id; UPROPERTY(EditAnywhere) FTransform Transform; UPROPERTY(EditAnywhere) float RadiusM = 8.f; };
UCLASS(BlueprintType) class APEX_API UApexRaceDefinition : public UPrimaryDataAsset {
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadOnly) FName RaceId;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) EApexRaceType Type = EApexRaceType::PointToPoint;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 Laps = 1;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) TArray<FApexCheckpointDefinition> Checkpoints;
  UPROPERTY(EditAnywhere, BlueprintReadOnly) int32 RewardHookId = 0;
};
