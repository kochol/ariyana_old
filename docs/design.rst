Design goals
============

The goal of this engine design is to make a fast engine.

Jobify the engine with fibers
-----------------------------

The first design goal is using fibers to jobify the engine and use all of the CPU cores.
For more info see
GDC talk by Christian Gyrling in his 2015 GDC Talk 'Parallelizing the Naughty Dog Engine Using Fibers'

Frame data
----------

Use frame data to enable the parallel work of different parts of the engine without waiting for
each other to finish their job.
For example gameplay systems update entities and send them to scene system then scene system store
them to perform culling and sorting next frame after that sends it to render system for next frame
rendering so rendering is always two frame behind gameplay systems this design makes every thing
works in parallel.
For more info see
GDC talk by Christian Gyrling in his 2015 GDC Talk 'Parallelizing the Naughty Dog Engine Using Fibers'

For this system to work I made different update stages that be called for every system that needs it.

Entity, Component and Node
--------------------------

This part of the design I got inspired by Godot engine where Components can attach to each other and
creates a tree.
The base class here is Node class that Entity and Component class are inherited from them so Components
can attach to entities and vice versa.
This design works well for example when you work on a project with your colleges and everyone can
work on a different entity without conflict.

Also, entities are useful when later we add networking to the engine.