# opengl-game-engine

## Current project state
![](https://i.imgur.com/bUdMwuJ.png)

## Installing dependencies
### Linux
#### GLEW
```
sudo apt install libglew-dev & libglm-dev & libglfw3-dev & libassimp-dev
```
### Windows
#### GLEW, glm, GLFW3
provided statically
#### Assimp
* download sources from: http://assimp.org/index.php/downloads
* generate Visual Studio Solution using CMake
* compile using Visual Studio
* copy .lib and .dll files (from lib/ and bin/) <br>

**dll should finally be in the same directory as an executable**

## Useful
### Point light attenuation
![](https://i.imgur.com/W1z0qHD.png)
### Materials
http://devernay.free.fr/cours/opengl/materials.html

## What I've learned
### Textures
#### When creating a texture you don't bind it to any particular texture unit
You do it when you actually wanna use it
#### Texture unit indexing
**GL_TEXTURE0 is not 0**
And because of that you set sampler2D like that
```cpp
setInt("texture_sampler", 2); // don't use GL_TEXTURE0 + 2 here!!
glActiveTexture(GL_TEXTURE0 + 2);
glBindTexture(GL_TEXTURE_2D, texture);
```
