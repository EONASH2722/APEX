# Testing

Cloud-native tests compile the standard C++ kernel and cover sea-level density, altitude/temperature independence, drag, downforce, drivetrain losses/split, rolling resistance and invalid profiles. Run:

```bash
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
```

The JSON validator intentionally rejects the unpopulated template. Unreal Automation tests remain required for serialization/migration, Chaos standing acceleration, braking, top-speed convergence, shifts, FWD/RWD/AWD behavior, surface transitions, environment zones and test-run CSV telemetry. These have not run because Unreal Engine 5.8 is unavailable in cloud. The migration status is **Implemented/migrated but requires local UE 5.8 validation**.
