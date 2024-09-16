Bolt Engine
=====

# Very simple render engine

Bolt engine is a very simple renderer that hopes to implement the following features:

- Abstract Renderable classes holding information about verticies, uvs, shaders, textures, ect..., 

- Subclases like VKRenderable and GLRenderable that provide high level abstraction features for with the ability to swap between rendering frameworks

- Mesh batching, rendering a signle mash multiple times,

- Camera culling determing what is inside the vision cone of the camera and only render that part

# Installing dependecies

To setup the projects run:
```sh
./scripts/setup.sh [Debug|Release]
```

This will install the correct dependecies needed for the projects and configure cmake

After that to build the project simply navigate to the build directory and run make:
```
cd ./build/
make
```

If succesfully compiled there should be a `BoltEngine` executible in your build directory that you can run.

# Project layout

The project can be split into a few different sections:

* Rendering,
  * common rendering classes (renderer, window),
  * framework specific stuff aka OpenGL and Vulkan classes,
  * The above will be two points above will be merget at some point becouse the vulkan API in this library is deprecated
* IO io handeling,
* events event system of the engine,
* primitives (this is basicly deprecates and will be deleted at some point)
* model - 3D model creation and handeling,
* core - core classes and utility,
* scene - scene layout and cameras

## Render thread

Rendering is done on a seperate thread.

The renderer is basically split up like this: The renderer contains scenes, witch contain
render interfaces, witch are responsible for separate shaders, VBOs, VAOs and textures.
Scenes also determine weather the render interfaces contained in it will draw to a separate
texture that can than be passed on for further post-processing.

## Logic thread

The logic thread (the main thread) is composed of layers. These layers are responsible for handeling
the user input, events, object interactions, physics calculations, ect... More or less everything and anything
that isn't related to rendering itself. However they do represent the order your objects get drawn in. You can 
imagine that the layers here are similar to layers in a drawing (a.k.a. they can represent the background, foreground, player GUI, etc...).
The order that the layers are adding their scenes to the renderer, thats the order the objects will be drawn in.
Keep in mind that the objects in the scene get renderer in the order they were added to it.
