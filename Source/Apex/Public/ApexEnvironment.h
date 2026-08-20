#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ApexEnvironment.generated.h"

USTRUCT(BlueprintType) struct FApexEnvironmentState {
  GENERATED_BODY()
  UPROPERTY(EditAnywhere, BlueprintReadWrite) float TemperatureC = 15.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite) float PressurePa = 101325.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite) float ElevationM = 0.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", ClampMax="1")) float RelativeHumidity = 0.f;
};
UCLASS(ClassGroup=(Apex), meta=(BlueprintSpawnableComponent)) class APEX_API UApexEnvironmentComponent : public UActorComponent {
  GENERATED_BODY()
public:
  UPROPERTY(EditAnywhere, BlueprintReadWrite) FApexEnvironmentState State;
  UFUNCTION(BlueprintPure) float GetAirDensityKgM3() const;
  UFUNCTION(BlueprintPure) float GetDragNewtons(float DragCoefficient, float FrontalAreaM2, float SpeedMps) const;
};
