# Architecture

`ApexPhysicsCore` is standard C++20 and has no Unreal dependency; equations and profile validation run in cloud CI. It remains intentionally unchanged by the UE 5.8 migration. `Apex` is the Unreal runtime module. Primary Data Assets carry vehicle, surface, and race definitions. Stable IDs—not map coordinates or asset pointers—form save-game identity.

The world will use World Partition and data layers. Region/biome, environmental, road-surface, traffic, race, police, spawn, weather and acoustic zones remain independent metadata layers. A biome selects defaults only; contact surface and sampled atmosphere drive physics. Content paths are `/Game/Apex/...`; licensed local packages live under ignored `/Game/ThirdParty` before migration.

Implemented Unreal foundations require compilation validation locally: sourced vehicle values, performance targets, surface profiles, race layouts, atmosphere/drag component, and versioned save container. Chaos pawn, tire force bridge, race state machine, garage service, camera, telemetry UI, traffic and police are explicitly not yet implemented.
