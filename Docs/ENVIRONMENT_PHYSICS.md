# Environment Physics

Atmosphere is described by temperature, absolute pressure, elevation and relative humidity. If pressure is absent, the portable kernel derives it from elevation using an ISA troposphere approximation. Humid density splits dry-air and water-vapor partial pressures. Drag is `0.5 rho Cd A v |v|`; negative lift coefficient yields downforce magnitude.

Zones must provide measured/configured variables rather than labels such as desert or forest. Surface profiles are separately selected from physical-material/contact metadata, so an asphalt desert highway remains asphalt. Default surface assets (dry/wet asphalt, concrete, dirt, gravel, sand, snow, ice and mud) must be created and tuned in the editor.
