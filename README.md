Bolt Engine
=====

# Very simple render engine

Bolt engine is a very simple renderer that hopes to implement the following features:

- Abstract Renderable classes holding information about verticies, uvs, shaders, textures, ect..., 

- Subclases like VKRenderable and GLRenderable that provide high level abstraction features for with the ability to swap between rendering frameworks

- Mesh batching, rendering a signle mash multiple times,

- Camera culling determing what is inside the vision cone of the camera and only render that part
