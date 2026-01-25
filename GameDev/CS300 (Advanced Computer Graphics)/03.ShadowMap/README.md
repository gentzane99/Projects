# CS300 — Assignment 3: Shadow Mapping with PCF (OpenGL)

Academic graphics project implemented in C++/OpenGL.  
This assignment implements **shadow mapping for a spotlight** using a **two-pass rendering pipeline** and **percentage-closer filtering (PCF)** to produce soft shadow edges, integrated into a Phong lighting model.

> This is an academic project. Assignment specifications are summarized and not reproduced verbatim.

## Highlights
- **Shadow mapping (two-pass pipeline)**
  - First pass renders scene depth from the light’s point of view
  - Second pass applies the shadow map during camera rendering :contentReference[oaicite:0]{index=0}
- **Percentage-Closer Filtering (PCF)**
  - Uniform multi-sample neighborhood for soft shadow edges
  - Adjustable kernel size at runtime :contentReference[oaicite:1]{index=1}
- **Spotlight shadows**
  - Light FOV matched to spotlight cone
  - Light always targets the central object
- **Procedural geometry**
  - Plane + shape library (Plane, Cube, Cone, Cylinder, Sphere)
  - Runtime subdivision control
- **Animated scene**
  - Rotating spotlight with sinusoidal vertical motion
  - Two adjacent animated objects to stress-test shadow stability
- **Debug & visualization**
  - Shadow map rendered to an on-screen viewport for inspection
  - Wireframe and normal visualization toggles

## Controls
### Camera
- `W/S` — Move up/down
- `A/D` — Move left/right
- `Q/E` — Move closer/farther

### Shapes & mesh resolution
- `1–5` — Select shape (Plane, Cube, Cone, Cylinder, Sphere)
- `+ / -` — Increase / decrease subdivisions

### Animation & rendering
- `P` — Pause / resume light animation
- `O` — Pause / resume adjacent object animation
- `M` — Toggle wireframe
- `F` — Toggle face vs averaged normals
- `N` — Toggle normal rendering

### PCF tuning
- `Z / X` — Increase / decrease PCF neighborhood size

### Object rotation
- Arrow keys — Rotate center object around X / Y axes

## Technical overview
### Shadow map generation
The scene is first rendered from the spotlight’s point of view to a depth texture. The light’s projection parameters are chosen to match the spotlight cone, ensuring efficient depth coverage and minimizing wasted shadow map space. :contentReference[oaicite:2]{index=2}

### Shadow usage & PCF
During the camera pass, each fragment is transformed into light space to compute shadow map UVs and depth. Visibility is evaluated by sampling a square neighborhood around the projected coordinate and averaging the results (uniform PCF), producing softer and more stable shadow edges. :contentReference[oaicite:3]{index=3}

### Lighting integration
The computed shadow factor modulates the Phong lighting contribution. Only a single spotlight is active in this assignment; normal mapping and multiple lights are intentionally disabled to keep the focus on shadowing correctness and quality.

### Scene setup
- Large ground plane aligned with the XZ plane
- One main object at the center
- Two adjacent animated objects offset along the X axis
- Small white sphere rendered to visualize the light position

## Build & run
- **IDE:** Visual Studio 2022
- **Configuration:** Release | x64

## Executable Build

A precompiled Windows build is available via GitHub Releases:

https://github.com/gentzane99/Projects/releases/tag/cs300-shadow-mapping-pcf-v1.0
