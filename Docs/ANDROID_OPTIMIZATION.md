# Android Optimization

Three provisional device tiers cap texture pools and shadows in `DefaultDeviceProfiles.ini`; they require UE 5.8 Device Profile matching rules and physical-device profiling before assignment. Android meshes derive from the PC master with progressive reduction, consolidated materials, smaller textures, simplified interior/glass/reflections and fewer audio/secondary-physics layers. Vehicle identity and authoritative physics data remain shared.

For the UE 5.8 local toolchain, Epic's current requirements document lists Android Studio Koala 2024.1.2 Patch 1, recommended target SDK 35 (minimum compile target 34), NDK r27c, Build-tools 35.0.1, OpenJDK 21.0.3, and minimum install SDK 26. Install these through UE's supported Android setup flow rather than committing workstation paths. SDK/NDK builds, shader complexity, thermal behavior and profile selection were not tested in cloud.
