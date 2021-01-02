# HEOS
> Hydrogen Electron Orbital Simulator

## Basic information

The GitHub repository (URL) hosting the term project: https://github.com/honestree/HEOS

HEOS can generate a 3D model by type in principal quantum number, azimuthal quantum number and magnetic quantum number.

User can use mouse to drag around the model, zoom in and zoom out.

![](https://i.imgur.com/nCMnrcS.png)

## The approach

The whole model is actually composed of lots of different sized tiny tetrahedron. The brighter the tetrahedron, the higher probablity a electron can be found at the center of the tetrahedron.

To create such model, HEOS would first create a list of lattice points. These points would later use single electron wave function to calcalate the probablity. Then a scene is created by adding tetrahedron by probablity and position.

![](https://i.imgur.com/41VUfMK.png)
> the single electron wavefunction given in spherical coordinate system

## How to start

### Dependency

* make 
* g++
* libglfw3-dev
* libglm-dev
* libglew-dev
* libxi-dev

### 
```
make
mkdir Models
./HEOS
```

You can also check main.cpp to learn how to link RequestDealer.

## Perspective users

For student that first learned a thing or two on Atomic Physic, and want to have a brief idea for what these quantum number might affect on the orbit model.

## System architecture

![](https://i.imgur.com/rYGtujQ.png)

## API description

* User Interface << UNCOMPLETED
    * Collect user input
        * to generate new model
        * to interact with current model
* Request Dealer
    * Collect quantum number and Graphical setting
    * Collect math result
    * Initiate model generation
* Probability Former
    * Calculate Probability by given input
* Model Generator
    * Generate model with given graphic setting
* Model Demonstrator
    * Demonstrate model
    * Respond to users action

## Engineering infrastructure

This project would use 
* C++ to perform math calculate
* OpenGL to render the model.

## TODO

* Better UI

## Schedule

|week|date|jobs|
|:-:|:---:|:--:|
|7  |10/26| Implement Model Demonstrator                      |
|8  |11/2 | Implement Model Generator                         |
|9  |11/9 | Implement Python API front-end and Request Dealer |
|10 |11/16| Implement Probability Generator                   |
|11 |11/23| Function Intergating                              |
|12 |11/30| pytest - Unitesting                               |
|13 |12/7 | Debugging and optimization                        |
|14 |12/14| Buffer week <br> Prepare for presentation.        |
|15 |12/21| Prepare for presentation                          |

  
## Reference
* https://github.com/opengl-tutorials/ogl
* https://en.wikipedia.org/wiki/Hydrogen_atom




