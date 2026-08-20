# APEX

APEX is a source-first Unreal Engine 5.8 open-world racing project. The confirmed local Windows toolchain is Unreal Engine 5.8, Visual Studio 2026, Blender, Git, and Codex Local. This cloud phase provides a tested, engine-independent physics kernel, Unreal data types and environment/save foundations, configuration, validation tools, and an honest local-integration runbook. It contains no third-party assets or fabricated editor binaries.

## Cloud quick start

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
python3 Scripts/Validation/validate_vehicle.py Scripts/VehicleData/vehicle_template.json # expected to reject the intentionally incomplete template
```

Start local integration at [the handoff](Docs/CLOUD_TO_LOCAL_HANDOFF.md). The current status is recorded in [the cloud report](Docs/CLOUD_PHASE_REPORT.md).

The source and configuration have been migrated for UE 5.8, but an Unreal Editor build is intentionally not claimed until the local UE 5.8 validation procedure has run.
