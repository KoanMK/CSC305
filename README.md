# CSC 305 A4

## Nigel Decontie V00853112

Basic Functionality:

Geometry:
- flat  (z=0)  triangular mesh. Done using GL_TRIANGLE_STRIP, making use of GL_PRIMITIVE_RESTART
- Perlin noise on CPU
- heightmap texture using fBm
- vertex displacement using the heightmap texture

Rendering:
- calculated sufacenormals
- textured according to height and slope
- skybox using cubemap textures

Animation
- WASD controls
