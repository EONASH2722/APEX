# Local Asset Manifest

| Asset | Expected staging path | Purpose | Status | License / processing / import |
|---|---|---|---|---|
| Japanese city map | `Content/ThirdParty/CitySource/` then migrate to `Content/Apex/Maps/City/` | Central region | Required | Confirm redistribution and plugin dependencies; migrate, fix redirects, enable World Partition; preserve source package settings. |
| Desert/canyon pack | `Content/ThirdParty/LandscapeSource/` then `Content/Apex/Environment/Desert/` | South region | Required | Existing purchase; confirm project-seat/distribution terms; import heightmaps at documented scale, landscape materials as instances. |
| Forest/mountain terrain | `Content/ThirdParty/LandscapeSource/` | North region | Required later | License unknown; validate scale/World Partition and collision. |
| Vehicle models | `SourceModels/<vehicle_id>/` | Driveable cars | One required for milestone | License per model; process derivative; FBX skeletal import in centimeters, X-forward/Z-up, import normals/tangents after validation. |
| Vegetation | `Content/ThirdParty/Vegetation/` | Regional foliage | Optional milestone | Verify commercial redistribution; Nanite/foliage/HLOD review. |
| Road assets | `Content/ThirdParty/Roads/` | Surface/traffic network | Required | Physical-material mapping and spline compatibility; do not derive surface from biome. |
| Textures/materials | `Content/ThirdParty/Textures/` | Environment/vehicle shading | Required | Record provenance; virtual texture/streaming and Android variants. |
| Audio | `Content/ThirdParty/Audio/` | Engine, tires, ambience | Required later | Licensed/generated only; loop cleanup and MetaSound layer mapping. |
