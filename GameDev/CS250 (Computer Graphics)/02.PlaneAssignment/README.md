## CS250 – Computer Graphics II  
### Assignments 4 & 5: Software Rendering Pipeline

This project contains my implementation of Assignments 4 and 5 for the CS250 Computer Graphics II course at DigiPen Institute of Technology.

The goal of these assignments was to build a **software-based 3D rendering pipeline**, focusing on transformations, visibility determination, and rasterization techniques commonly used in real-time graphics.

---

### Assignment 4 – Axis-Angle Rotation, Orthogonal Matrix & Depth Buffering

Implemented core transformation and depth handling features, including:
- Model-to-world transformations using the airplane’s local axes
- World-to-camera transformation using an orthogonal view matrix
- Multiple camera modes (first person, third person, rooted camera)
- Depth buffer creation, initialization, and per-frame clearing
- Depth-aware triangle rasterization

This assignment focused on correct spatial transformations and visibility ordering using a depth buffer.

---

### Assignment 5 – Culling, Back-Face Removal & Clipping

Extended the rendering pipeline with additional visibility optimizations:
- Frustum plane generation in world space
- Object culling against the view frustum
- Back-face removal in world space
- Clipping against the near plane
- Transformation of newly generated geometry through the pipeline
- Final rasterization with depth buffering

This assignment emphasized performance-oriented rendering techniques by reducing unnecessary geometry processing.

---

### Controls

- **1–5**: Rendering and camera modes (wireframe, solid, first person, third person, rooted)
- **W / A / S / D / Q / E**: Pitch, roll, and yaw rotations
- **Space**: Move airplane forward
- **Z / X**: Decrease / increase camera distance
- **H / Y**: Decrease / increase camera height

---

### Technical Focus

- Software rendering (no hardware pipeline)
- Coordinate space transformations
- Camera systems
- Visibility determination (culling, clipping)
- Depth buffering and rasterization

---

## Build & Run

- **IDE:** Visual Studio 2022
- **Recommended configuration:** Debug | x64  
- The project can also be built in Release and other platforms.

---

## Executable Build

A precompiled Windows build is available via GitHub Releases:

https://github.com/gentzane99/Projects/releases/tag/cs250-plane-v1.0
