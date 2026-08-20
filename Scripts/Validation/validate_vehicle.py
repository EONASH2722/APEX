#!/usr/bin/env python3
"""Validate source vehicle JSON without guessing missing real-world data."""
import argparse, json, sys
from pathlib import Path

def validate(data):
    errors=[]
    if data.get("schema_version") != 1: errors.append("schema_version must be 1")
    if not data.get("vehicle_id") or data["vehicle_id"] == "replace_with_stable_id": errors.append("vehicle_id must be replaced")
    mass=data.get("mass", {})
    if mass.get("value") is None: errors.append("mass.value is required (leave null only in a research draft)")
    elif mass["value"] <= 0: errors.append("mass.value must be positive")
    for field in ("unit", "confidence"): 
        if not mass.get(field): errors.append(f"mass.{field} is required")
    ratios=data.get("transmission", {}).get("gear_ratios", [])
    if not ratios or any(not isinstance(x,(int,float)) or x <= 0 for x in ratios): errors.append("positive forward gear_ratios are required")
    return errors

def main():
    parser=argparse.ArgumentParser(); parser.add_argument("profile", type=Path); args=parser.parse_args()
    data=json.loads(args.profile.read_text(encoding="utf-8")); errors=validate(data)
    for error in errors: print(f"ERROR: {error}", file=sys.stderr)
    print(f"{args.profile}: {'valid' if not errors else str(len(errors)) + ' error(s)'}")
    return 1 if errors else 0
if __name__ == "__main__": raise SystemExit(main())
