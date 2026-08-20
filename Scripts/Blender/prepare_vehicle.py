"""Non-destructive Blender entry point; execute only inside Blender 4.x.

Usage: blender --background source.blend --python prepare_vehicle.py -- --output processed.blend
"""
import argparse, sys
try:
    import bpy
except ImportError:
    raise SystemExit("This script requires Blender's Python runtime; no model was modified.")

args=sys.argv[sys.argv.index("--")+1:] if "--" in sys.argv else []
p=argparse.ArgumentParser(); p.add_argument("--output", required=True); options=p.parse_args(args)
for obj in bpy.context.scene.objects:
    obj.name = obj.name.strip().lower().replace(" ", "_")
    if obj.type == "MESH":
        for polygon in obj.data.polygons: polygon.use_smooth = True
bpy.ops.wm.save_as_mainfile(filepath=options.output, copy=True)
print("Saved non-destructive processed derivative:", options.output)
