#pragma once

#include <optional>
#include <string>
#include <vector>

namespace apex {

enum class Confidence { Unknown, Estimate, SecondarySource, Manufacturer };
enum class DriveType { FrontWheelDrive, RearWheelDrive, AllWheelDrive };

template <typename T> struct SourcedValue {
  std::optional<T> value;
  std::string unit;
  std::string sourceUrl;
  std::string sourceName;
  Confidence confidence{Confidence::Unknown};
  std::string notes;
  int modelYear{};
  std::string trim;
};

struct Atmosphere {
  double temperatureC{15.0};
  std::optional<double> pressurePa;
  double elevationM{};
  double relativeHumidity{}; // [0, 1]
};

struct AeroProperties {
  double dragCoefficient{};
  double frontalAreaM2{};
  double liftCoefficient{}; // negative produces downforce
};

struct SurfaceProperties {
  std::string id;
  double frictionCoefficient{1.0};
  double rollingResistanceCoefficient{0.015};
  double longitudinalGripMultiplier{1.0};
  double lateralGripMultiplier{1.0};
};

struct Drivetrain {
  DriveType type{DriveType::RearWheelDrive};
  std::vector<double> forwardGearRatios;
  double reverseRatio{-3.0};
  double finalDriveRatio{1.0};
  double efficiency{0.85};
  double frontTorqueFraction{};
};

struct VehicleProfile {
  std::string id;
  SourcedValue<double> massKg;
  SourcedValue<double> wheelRadiusM;
  SourcedValue<double> wheelbaseM;
  SourcedValue<double> trackWidthM;
  SourcedValue<double> maxBrakeForceN;
  AeroProperties aero;
  Drivetrain drivetrain;
};

struct ValidationIssue { std::string field; std::string message; bool error; };

double SaturationVaporPressurePa(double temperatureC);
double PressureAtElevationPa(double elevationM, double seaLevelPressurePa = 101325.0);
double AirDensityKgM3(const Atmosphere& atmosphere);
double AerodynamicDragN(const AeroProperties& aero, double airDensityKgM3, double velocityMps);
double AerodynamicDownforceN(const AeroProperties& aero, double airDensityKgM3, double velocityMps);
double WheelTorqueNm(double engineTorqueNm, double gearRatio, const Drivetrain& drivetrain);
double DrivenWheelTorqueNm(double totalWheelTorqueNm, const Drivetrain& drivetrain, bool frontAxle);
double RollingResistanceN(double massKg, const SurfaceProperties& surface, double gradeRadians = 0.0);
std::vector<ValidationIssue> Validate(const VehicleProfile& profile);

} // namespace apex
