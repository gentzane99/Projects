# CS300 — Assignment 2: Normal Mapping (OpenGL)

Academic graphics project implemented in C++/OpenGL.  
This assignment extends a Phong-based rendering pipeline with full **tangent-space normal mapping**, including per-vertex tangent and bitangent generation and multiple debug visualization modes.

> This is an academic project. Assignment specifications are summarized and not reproduced verbatim.

## Highlights
- **Tangent-space normal mapping**
  - Per-triangle tangent & bitangent computation from positions and UVs 
  - Gram–Schmidt orthonormalization to enforce T ⟂ N 
  - Normal, tangent, and bitangent uploaded as per-vertex attributes
- **Shader pipeline (GLSL)**
  - Correct transformation of N, T, B to camera space
  - Tangent → camera space matrix construction in fragment shader
  - Phong illumination using normal map–derived normals
- **Procedural geometry**
  - Plane, Cube, Cone, Cylinder, Sphere (from previous shape library)
  - Adjustable subdivision levels at runtime
- **Debug visualization modes**
  - Normal, Tangent, Bitangent visualized as RGB in camera space
- **Lighting system**
  - Point, Spot, Directional light modes
  - Animated light rig rotating around the scene
- **Interactive camera**
  - Orbit-style movement while always looking at the object

## Controls
### Camera
- `W/S` — Move up/down
- `A/D` — Move left/right
- `Q/E` — Move closer/farther

### Shape & mesh resolution
- `1–5` — Select shape (Plane, Cube, Cone, Cylinder, Sphere)
- `+ / -` — Increase / decrease subdivisions

### Lighting & rendering
- `7` — Point lights
- `8` — Spot lights
- `9` — Directional lights
- `P` — Pause / resume light animation
- `M` — Toggle wireframe
- `F` — Toggle face vs averaged normals
- `N` — Toggle normal rendering

### Rendering modes
- `T` — Cycle render modes:
  - **Normal Mapping** — Phong lighting with normal map
  - **Normals** — Geometry normal (camera space) as color
  - **Tangent** — Tangent vector (camera space) as color
  - **Bitangent** — Bitangent vector (camera space) as color

### Object rotation
- Arrow keys — Rotate object around X / Y axes

## Technical overview
### Tangent-space construction
For each triangle, tangent and bitangent vectors are computed using vertex positions and texture coordinates. Tangents are orthonormalized against the geometric normal using Gram–Schmidt to ensure a stable tangent basis before being sent to the GPU.

### Shader workflow
- **Vertex shader**
  - Normal transformed using the normal matrix
  - Tangent and bitangent transformed using model and view matrices
- **Fragment shader**
  - Normal map sampled and remapped from [0,1] to [-1,1]
  - TBN matrix built to transform normals from tangent space to camera space
  - Resulting normal used in the Phong reflection model

### Scene setup
- Ground plane aligned with XZ plane
- One procedural object rendered at a time
- Lights distributed along a circular path and animated over time
- Small white spheres rendered to visualize light positions

## Build & run
- **IDE:** Visual Studio 2022
- **Configuration:** Release | x64

## Executable Build

A precompiled Windows build is available via GitHub Releases:

https://github.com/gentzane99/Projects/releases/tag/cs300-normal-mapping-v1.0
