#include "ApexEnvironment.h"
#include "Math/UnrealMathUtility.h"
float UApexEnvironmentComponent::GetAirDensityKgM3() const {
  const double Kelvin = State.TemperatureC + 273.15;
  if (Kelvin <= 0.) return 0.f;
  const double Saturation = 610.94 * FMath::Exp(17.625 * State.TemperatureC / (State.TemperatureC + 243.04));
  const double Vapor = FMath::Clamp(State.RelativeHumidity, 0.f, 1.f) * Saturation;
  return static_cast<float>(FMath::Max(0., State.PressurePa - Vapor) / (287.058 * Kelvin) + Vapor / (461.495 * Kelvin));
}
float UApexEnvironmentComponent::GetDragNewtons(float Cd, float Area, float Speed) const { return .5f * GetAirDensityKgM3() * Cd * Area * Speed * FMath::Abs(Speed); }
