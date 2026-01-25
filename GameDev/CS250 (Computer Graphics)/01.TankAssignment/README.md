# CS250 – Assignments 2–3: Software Rendering & Camera Systems

This project contains my implementation of **Assignments 2 and 3** for the **CS250 – Computer Graphics II** course at DigiPen Institute of Technology.

The focus of these assignments is the construction of a **basic software 3D rendering pipeline**, including hierarchical transformations, perspective projection, and multiple camera systems.

---

## Assignment 2 – Simple Perspective Projection & Transformations

This assignment introduces the foundations of the rendering pipeline and object hierarchies.

Implemented features include:
- Model-to-world transformations using a matrix stack
- Hierarchical transformations for a tank model composed of multiple parts:
  - Body
  - Turret
  - Gun
  - Four wheels
- Simple perspective projection
- Projection-to-viewport transformation
- Line and triangle rasterizers
- Wireframe and solid rendering modes

The tank is built from cube primitives defined in an input file, and transformations propagate through the hierarchy using parent–child relationships.

---

## Assignment 3 – Viewing Matrix & Camera Systems

This assignment extends the pipeline with camera control and viewing transformations.

Implemented features include:
- World-to-camera transformation using the general rotation method
- Multiple camera modes:
  - First-person camera (attached to the turret)
  - Third-person camera (following the tank with adjustable distance and height)
  - Fixed/rooted camera
- Dynamic computation of camera position, view, right, and up vectors
- Perspective projection including near and far planes
- NDC-to-viewport transformation
- Scene population with a grid of cubes for spatial reference
- Basic culling in camera space

This assignment focuses on correct camera behavior and coordinate space transformations.

---

## Controls

### Rendering / Camera modes
- **1** – Wireframe mode  
- **2** – Solid mode  
- **3** – First-person camera  
- **4** – Third-person camera  
- **5** – Rooted camera  

### Tank controls
- **A / D** – Rotate tank body  
- **Q / E** – Rotate turret  
- **R / F** – Rotate gun up / down  
- **Space** – Move tank forward  

### Camera adjustment (third person)
- **Z / X** – Decrease / increase camera distance  
- **H / Y** – Decrease / increase camera height  

---

## Build & Run

- **IDE:** Visual Studio 2022
- **Recommended configuration:** Debug | x64  
- The project can also be built in Release and other platforms.

---

## Code Notes

- Matrix and transformation logic is primarily implemented in `Object.cpp`
- Camera position and vector calculations are handled in `main.cpp`

---

## Executable Build

A precompiled Windows build is available via GitHub Releases:

https://github.com/gentzane99/Projects/releases/tag/cs250-tank-v1.0

