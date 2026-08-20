# PC Rendering

The target baseline is 1080p on an RTX 3050-class 6 GB GPU. Lumen and Nanite are enabled as project capabilities, not performance guarantees. Medium targets a roughly 3 GB streaming pool; High 4 GB, preserving headroom for render targets and geometry. Use Unreal Insights, `stat unit`, `stat gpu`, `stat streaming`, Render Resource Viewer and representative night/rain scenes locally. Cinematic settings may exceed baseline; vehicle materials should share clear-coat master instances.
