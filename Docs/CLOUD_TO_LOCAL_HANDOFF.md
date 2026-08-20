# Cloud to Local Handoff

## Exact local procedure

1. Install **Unreal Engine 5.8** and **Visual Studio 2026** on Windows with the Game development with C++ workload, Unreal Engine tools, and a Windows SDK supported by the installed UE 5.8 build. Install Blender separately if vehicle processing is needed.
2. Confirm plugins in `APEX.uproject`: Chaos Vehicles, Enhanced Input, MetaSounds; Modeling Tools is editor-only. Do not upgrade engine/plugin versions in the first validation pass.
3. Complete the **First UE 5.8 Validation** below before creating or migrating assets; cloud did not have Unreal headers or UnrealBuildTool.
4. Stage the licensed city under ignored `Content/ThirdParty/CitySource`, open its vendor project if required, and **Migrate** dependencies to this project. Move curated content to `/Game/Apex/Maps/City` inside Content Browser and fix redirectors.
5. Stage/migrate the landscape pack similarly into `/Game/Apex/Environment/Desert`; retain source scale/import documentation. Do not merge the full landscape before the small driving map passes.
6. Place immutable car source files in ignored `SourceModels/<vehicle_id>/`. Never overwrite them.
7. Run `blender --background SourceModels/<id>/source.blend --python Scripts/Blender/prepare_vehicle.py -- --output ProcessedModels/<id>/prepared.blend`. Inspect it visually; complete wheel separation, origins, rig, collision and LOD tasks listed in the pipeline document.
8. Export an FBX derivative using centimeters, X-forward and Z-up. Import into `/Game/Apex/Vehicles/<id>/Meshes`; verify transforms, skeleton/wheel bones, materials, normals, collision and dimensions.
9. In Editor create a `UApexVehicleSpecification` under `/Game/Apex/Vehicles/Data`, surface profile assets, Enhanced Input Actions/Mapping Context, Chaos wheel/pawn Blueprint subclasses, licensed MetaSounds, a World Partition test map and a simple Race Definition. No `.uasset` is fabricated in this repository.
10. Run native tests first. Then add/run Unreal Automation tests named in `Docs/TESTING.md`, validate dimensions against researched data, inspect Message Log, and capture telemetry/performance evidence.
11. Launch the small test map, spawn the single Chaos vehicle, possess it, check throttle/brake/steer/handbrake/gears, cross two physical surfaces, vary environment state, run acceleration/braking, inspect telemetry, save, and complete a two-checkpoint race.
12. Only after that passes, migrate the complete city and landscapes and configure World Partition data layers/HLODs.

## First UE 5.8 Validation

Codex Local must perform this gate before feature development or proprietary asset integration:

1. Confirm `APEX.uproject` opens with the installed UE 5.8 build. If Windows has not associated the project, select UE 5.8 explicitly.
2. Generate Visual Studio project files when they are absent or stale, either from the `.uproject` shell action or UE 5.8's supported project-file generator.
3. Open the generated solution in Visual Studio 2026 and compile the **ApexEditor** target in **Development Editor / Win64**. Preserve the first complete build log.
4. Open APEX in UE 5.8. Review and fix genuine compiler, deprecation, configuration and migration warnings; do not suppress warnings merely to make the log quiet. Commit compatibility fixes separately with their evidence.
5. In Plugins, verify **Chaos Vehicles**, **Enhanced Input**, and **MetaSounds** are enabled and load without errors. Verify Modeling Tools Editor Mode remains editor-only.
6. Confirm the `Apex` runtime module loads. Create or inspect a `UApexVehicleSpecification` and verify Asset Manager registration resolves `VehicleSpecification` assets under `/Game/Apex/Vehicles/Data`.
7. Verify Enhanced Input user settings initialize, and create a minimal temporary MetaSound only to confirm the editor integration; no copyrighted audio is required.
8. Run native tests and all available Unreal Automation tests, then open and run the first small driving test map. If that map has not yet been authored, create only the local placeholder described in `LOCAL_PHASE_TASKS.md` and record that dependency instead of claiming a pass.

Successful native tests alone do not satisfy this gate. Until these steps run locally, status remains **Implemented/migrated but requires local UE 5.8 validation**.

## UE 5.8 migration audit

- `EngineAssociation` is pinned to `5.8`; game/editor target names and module loading remain conventional.
- `BuildSettingsVersion.V5`, `PCHUsageMode.UseExplicitOrSharedPCHs`, and the current target/module rules were retained rather than guessing at an unverified build-default change. UE 5.8 UnrealBuildTool warnings from the first local build determine whether a newer explicit build settings version is required.
- Plugin identifiers remain `ChaosVehiclesPlugin`, `EnhancedInput`, `Metasound`, and editor-only `ModelingToolsEditorMode`. Runtime module dependencies remain `EnhancedInput`, `ChaosVehicles`, and `AudioMixer`; no API in the current source requires an additional MetaSound module.
- Asset Manager configuration continues to scan the native `UApexVehicleSpecification` class under `/Game/Apex/Vehicles/Data`. Validate discovery in-editor because no Asset Registry exists in cloud.
- Renderer/scalability CVars were not changed without measured UE 5.8 evidence. Android device profiles now live in `DefaultDeviceProfiles.ini`, not `DefaultScalability.ini`.
- Enhanced Input's `bEnableUserSettings` remains configured, but mappings are intentionally local/editor assets. No Chaos, input, or MetaSound binary asset was fabricated.

Reference the official [UE 5.8 Visual Studio setup](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine?application_version=5.8) and [UE 5.8 Android requirements](https://dev.epicgames.com/documentation/en-us/unreal-engine/android-development-requirements-for-unreal-engine?application_version=5.8) when provisioning local machines; workstation-specific SDK paths must not be committed.

## Unresolved and cloud limitations

The Chaos pawn/wheels/input assets, camera, HUD/telemetry exporter, full race state machine, garage spawning, surface physical materials, test map, MetaSounds, World Partition configuration and content assets remain local work or further source work. Unreal Engine 5.8 Editor/UnrealBuildTool, Visual Studio 2026, Blender execution, Android SDK/NDK, GPU rendering, proprietary packages and visual inspection were unavailable in cloud; none was claimed tested.
