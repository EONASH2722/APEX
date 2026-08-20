#include "ApexPhysics.h"
#include <algorithm>
#include <cmath>

namespace apex {
namespace { constexpr double kGasConstantDryAir = 287.058; constexpr double kGasConstantVapor = 461.495; constexpr double kGravity = 9.80665; }

double SaturationVaporPressurePa(double temperatureC) {
  // Magnus formula is sufficiently accurate for normal vehicle operating climates.
  return 610.94 * std::exp((17.625 * temperatureC) / (temperatureC + 243.04));
}

double PressureAtElevationPa(double elevationM, double seaLevelPressurePa) {
  // ISA troposphere approximation. Elevation is independent input, not inferred from biome.
  const double base = 1.0 - 2.25577e-5 * elevationM;
  return seaLevelPressurePa * std::pow(std::max(base, 0.01), 5.25588);
}

double AirDensityKgM3(const Atmosphere& atmosphere) {
  const double temperatureK = atmosphere.temperatureC + 273.15;
  if (temperatureK <= 0.0) return 0.0;
  const double pressure = atmosphere.pressurePa.value_or(PressureAtElevationPa(atmosphere.elevationM));
  const double vaporPressure = std::clamp(atmosphere.relativeHumidity, 0.0, 1.0) * SaturationVaporPressurePa(atmosphere.temperatureC);
  const double dryPressure = std::max(0.0, pressure - vaporPressure);
  return dryPressure / (kGasConstantDryAir * temperatureK) + vaporPressure / (kGasConstantVapor * temperatureK);
}

double AerodynamicDragN(const AeroProperties& aero, double density, double velocity) {
  return 0.5 * density * aero.dragCoefficient * aero.frontalAreaM2 * velocity * std::abs(velocity);
}

double AerodynamicDownforceN(const AeroProperties& aero, double density, double velocity) {
  return std::max(0.0, -0.5 * density * aero.liftCoefficient * aero.frontalAreaM2 * velocity * velocity);
}

double WheelTorqueNm(double engineTorque, double gearRatio, const Drivetrain& drivetrain) {
  return engineTorque * gearRatio * drivetrain.finalDriveRatio * std::clamp(drivetrain.efficiency, 0.0, 1.0);
}

double DrivenWheelTorqueNm(double total, const Drivetrain& drivetrain, bool frontAxle) {
  double front = drivetrain.frontTorqueFraction;
  if (drivetrain.type == DriveType::FrontWheelDrive) front = 1.0;
  if (drivetrain.type == DriveType::RearWheelDrive) front = 0.0;
  front = std::clamp(front, 0.0, 1.0);
  return total * (frontAxle ? front : 1.0 - front);
}

double RollingResistanceN(double mass, const SurfaceProperties& surface, double grade) {
  return std::max(0.0, mass) * kGravity * std::cos(grade) * std::max(0.0, surface.rollingResistanceCoefficient);
}

std::vector<ValidationIssue> Validate(const VehicleProfile& p) {
  std::vector<ValidationIssue> out;
  auto requiredPositive = [&out](const SourcedValue<double>& v, const char* field) {
    if (!v.value) out.push_back({field, "required value is unavailable", true});
    else if (*v.value <= 0.0) out.push_back({field, "must be positive", true});
    if (v.value && v.confidence == Confidence::Unknown) out.push_back({field, "value lacks confidence classification", false});
  };
  if (p.id.empty()) out.push_back({"id", "stable vehicle identifier is required", true});
  requiredPositive(p.massKg, "massKg"); requiredPositive(p.wheelRadiusM, "wheelRadiusM");
  if (p.aero.dragCoefficient <= 0.0 || p.aero.frontalAreaM2 <= 0.0) out.push_back({"aero", "drag coefficient and frontal area must be positive", true});
  if (p.drivetrain.forwardGearRatios.empty()) out.push_back({"drivetrain.forwardGearRatios", "at least one forward gear is required", true});
  for (double ratio : p.drivetrain.forwardGearRatios) if (ratio <= 0.0) out.push_back({"drivetrain.forwardGearRatios", "forward ratios must be positive", true});
  if (p.drivetrain.efficiency <= 0.0 || p.drivetrain.efficiency > 1.0) out.push_back({"drivetrain.efficiency", "must be in (0, 1]", true});
  return out;
}
} // namespace apex
