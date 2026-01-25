# ProjectName — CS300 Assignments 0–1: Shape Library & Phong Illumination (OpenGL)

Academic graphics project built in C++/OpenGL. The project generates a small library of procedural meshes and renders them with a configurable Phong lighting pipeline implemented in GLSL.

> This is an academic project. Assignment specifications are summarized and not reproduced verbatim.

## Highlights
- **Procedural mesh generation** (unit-sized, centered at origin):
  - Plane, Cube, Cone, Cylinder, Sphere :contentReference[oaicite:1]{index=1}
- **Per-vertex attributes**:
  - Position, Normal, UV coordinates :contentReference[oaicite:2]{index=2}
- **Normal workflows**
  - Face normals vs averaged (vertex) normals toggle :contentReference[oaicite:3]{index=3}
  - Optional normal visualization mode :contentReference[oaicite:4]{index=4}
- **Shader-based Phong illumination (GLSL)**
  - Vertex + fragment shaders loaded from external files (no embedded shader strings) :contentReference[oaicite:5]{index=5}
  - Lighting supports **point / spot / directional** modes :contentReference[oaicite:6]{index=6}
- **Scene / interaction**
  - Orbit-style camera controls while always looking at the object :contentReference[oaicite:7]{index=7}
  - Animated light rig (toggleable) :contentReference[oaicite:8]{index=8}

## Controls
### Shape selection / mesh resolution
- `1–5` — Select shape (Plane, Cube, Cone, Cylinder, Sphere)
- `+` / `-` — Increase / decrease shape subdivisions (slices/rings depending on shape)

### Rendering toggles
- `N` — Toggle normal rendering/visualization
- `T` — Toggle texture mapping on/off
- `F` — Toggle face normals vs averaged normals
- `M` — Toggle wireframe mode on/off

### Object rotation
- Arrow keys — Rotate the object around X/Y axes

### Camera
- `W/S` — Move up/down
- `A/D` — Move left/right
- `Q/E` — Move closer/farther

### Lighting
- `P` — Pause/resume light animation
- Light type selection (as implemented in this build):
  - `7` — Point lights
  - `8` — Spot lights
  - `9` — Directional lights

## Tech notes
### Shape library
Each primitive is generated procedurally and expanded into triangles for rendering through OpenGL vertex arrays (no third-party geometry drawing helpers). Per-vertex normals and UVs are computed during construction, with a switchable normal strategy:
- **Face normals**: one normal per triangle (flat shading)
- **Averaged normals**: accumulated and normalized per shared position (smooth shading)

### Phong shading pipeline
The GLSL pipeline implements the Phong model with ambient, diffuse, and specular terms, plus attenuation for positional lights. Shader compilation/linking errors are surfaced with enough context to identify the shader file responsible. :contentReference[oaicite:9]{index=9}

## Build & run
- **IDE:** Visual Studio 2022
- **Config:** Release | x64

A playable Windows build is available in **GitHub Releases** (includes the executable and required runtime dependencies).