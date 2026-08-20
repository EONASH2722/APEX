# Asset Pipeline

Source models are immutable and ignored under `SourceModels/`; derivatives go to ignored `ProcessedModels/`. Run Blender's background mode with `Scripts/Blender/prepare_vehicle.py`; it currently normalizes names, enables smooth polygons and saves a copy. It does **not** yet separate wheels, rig, generate collision/LODs or certify normals.

Before import record bounding dimensions, wheelbase, tracks, tire/wheel diameters and ride height and compare with sourced specs. Flag discrepancies rather than deforming proportions. Local processing must establish body, four wheels, brakes, calipers, glass, lights, interior, steering wheel and exhaust; verify centimeters, X-forward/Z-up, pivots, material slots and skeletal hierarchy. PC master generates Android derivatives—never a disconnected model.
