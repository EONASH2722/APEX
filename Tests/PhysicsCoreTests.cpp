#include "ApexPhysics.h"
#include <cmath>
#include <iostream>
#include <string>

namespace { int failures = 0; void check(bool ok, const std::string& message) { if (!ok) { std::cerr << "FAIL: " << message << '\n'; ++failures; } } }

int main() {
  using namespace apex;
  check(std::abs(AirDensityKgM3({15.0, 101325.0, 0.0, 0.0}) - 1.225) < 0.002, "ISA sea-level density");
  check(AirDensityKgM3({35.0, std::nullopt, 0.0, 0.2}) > AirDensityKgM3({5.0, std::nullopt, 2200.0, 0.2}), "pressure altitude remains independent of temperature");
  check(std::abs(AerodynamicDragN({0.30, 2.2, -0.1}, 1.225, 30.0) - 363.825) < 0.01, "drag equation");
  check(AerodynamicDownforceN({0.30, 2.2, -0.1}, 1.225, 30.0) > 0.0, "negative lift coefficient creates downforce");
  Drivetrain awd{DriveType::AllWheelDrive, {3.2, 2.1}, -3.0, 4.0, 0.9, 0.4};
  const double torque = WheelTorqueNm(300.0, 3.2, awd);
  check(std::abs(torque - 3456.0) < 0.01, "drivetrain loss and gearing");
  check(std::abs(DrivenWheelTorqueNm(torque, awd, true) / torque - 0.4) < 1e-9, "AWD split");
  check(RollingResistanceN(1500.0, {"asphalt", 1.0, 0.015, 1.0, 1.0}) > 220.0, "rolling resistance");
  VehicleProfile invalid; invalid.aero = {0.0, 0.0, 0.0}; invalid.drivetrain.efficiency = 2.0;
  check(Validate(invalid).size() >= 5, "profile validator reports missing and invalid data");
  if (failures == 0) std::cout << "All APEX physics core tests passed\n";
  return failures == 0 ? 0 : 1;
}
