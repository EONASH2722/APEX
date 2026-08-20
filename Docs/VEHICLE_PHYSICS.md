# Vehicle Physics

The portable kernel implements humid-air density, ISA pressure versus elevation, quadratic drag/downforce, gearing and drivetrain efficiency, AWD axle torque distribution, rolling resistance, and profile validation. Results—not target times—must emerge from mass, torque curve, gearing, tires, losses and aerodynamics. Performance targets are comparison data only.

Chaos integration must consume `UApexVehicleSpecification`. The first local implementation should preserve Chaos suspension/contact solving while applying environmental aerodynamic forces and surface multipliers. Tire foundations should expose longitudinal/lateral slip, slip angle, normal load, wheel angular speed and friction circle saturation. Temperature, pressure, wear, compound and damage are extension points; scripted drift yaw is forbidden. ABS, traction and stability control must be independent assist layers.
