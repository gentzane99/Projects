# CS300 — Assignment 4: Reflection & Refraction with Cube Mapping (OpenGL)

Academic graphics project implemented in C++/OpenGL.  
This assignment implements **real-time environment mapping** using **dynamically generated cube maps**, supporting both **reflection and refraction** on a central object.

> This is an academic project. Assignment specifications are summarized and not reproduced verbatim.

## Highlights
- **Dynamic cube map generation**
  - Six environment faces rendered every frame from the object’s position
  - Camera aligned with world axes (+X, −X, +Y, −Y, +Z, −Z) and 90° FOV
- **Two-pass rendering pipeline**
  - Pass 1: render environment into cube map via FBOs
  - Pass 2: render scene using the generated environment map
- **Reflection & refraction**
  - World-space reflection and refraction vectors
  - Configurable rendering modes (textured / reflective / refractive)
  - Refractive index set to 1.33 (glass-like material)
- **Skybox rendering**
  - Cube-based skybox always centered on the camera
  - Depth testing and face culling disabled for correct inside rendering
- **Procedural geometry**
  - Plane, Cube, Cone, Cylinder, Sphere from the shape library
  - Adjustable subdivision levels at runtime
- **Animated scene elements**
  - Two adjacent animated objects reflected in the environment map

## Controls
### Camera
- `W/S` — Move up/down  
- `A/D` — Move left/right  
- `Q/E` — Move closer/farther  

### Shapes & mesh resolution
- `1–5` — Select shape (Plane, Cube, Cone, Cylinder, Sphere)
- `+ / -` — Increase / decrease subdivisions

### Rendering & animation
- `T` — Cycle render modes:
  - Textured
  - Reflective (environment reflection)
  - Refractive (environment refraction)
- `O` — Pause / resume adjacent object animation
- `M` — Toggle wireframe
- `F` — Toggle face vs averaged normals

### Environment textures
- `Z` — Cubemap texture set
- `X` — Alternate (“cotton candy”) texture set

### Object rotation
- Arrow keys — Rotate center object around X / Y axes

## Technical overview
### Cube map construction
Each frame, the scene is rendered six times into a cube map, with the virtual camera placed at the center of the reflective/refractive object. Each pass uses a 90° field of view and square aspect ratio to correctly cover one cube face.

### Environment sampling
In the environment-mapped pass, reflection or refraction vectors are computed in world space from the view direction and surface normal. These vectors are used directly to sample the cube map and fetch the environment color.

### Rendering constraints
To keep the focus on environment mapping:
- Lighting, normal mapping, and shadow mapping are disabled
- Adjacent objects use simple textured shading
- The central object exclusively demonstrates reflection/refraction behavior

### Scene setup
- Large ground plane aligned with the XZ plane
- One main object rendered at the center
- Two adjacent animated objects offset along the X axis
- Skybox rendered first to establish the environment

## Build & run
- **IDE:** Visual Studio 2022
- **Configuration:** Release | x64 

## Executable Build

A precompiled Windows build is available via GitHub Releases:

https://github.com/gentzane99/Projects/releases/tag/cs300-cubemap-reflection-refraction-v1.0
