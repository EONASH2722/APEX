# Vehicle Data

Each measurement uses a value-presence flag plus unit, URL, source name, confidence, notes, model year and trim. `Unknown` differs from `EngineeringEstimate`; missing values are not zero. The Unreal schema is in `ApexDataTypes.h`; the research interchange template is `Scripts/VehicleData/vehicle_template.json`.

Workflow: copy the template, assign a stable lowercase ID, research exact year/trim, retain conflicting sources in notes, classify estimates, validate JSON, then create a local Primary Data Asset. No roster has been invented. Torque curves should use measured/manufacturer points; digitized estimates must say so.
