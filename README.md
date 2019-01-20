# Ariyana

[![Contribute!](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](https://github.com/kochol/ariyana/issues)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/kochol/ariyana/blob/master/LICENSE)

Ariyana is a WIP game engine that is planned to include these features.

## Planned features

- Cross-platform
  - Windows
  - Linux
  - Android
- Fast
  - I try to make the engine easy to use but the performance is the high priority, There are many easy to use engine out there already.
  - Using fibers to jobify the engine
  - Using frame buffers that is introduced in GDC talk by Christian Gyrling in his 2015 GDC Talk 'Parallelizing the Naughty Dog Engine Using Fibers'
- Entity component system
- Editor
  - Easy to use
  - Animate every thing
  - Json save and load for easy team support and Git.
  
## How to build
https://github.com/kochol/ariyana/blob/master/docs/building.rst

## Dependencies

- [bgfx](https://github.com/bkaradzic/bgfx) rendering library
- [bimg](https://github.com/bkaradzic/bimg) image library
- [bx](https://github.com/bkaradzic/bx) core library
- [brtshaderc](https://github.com/fredakilla/brtshaderc) runtime shader compiler for bgfx
- [dear imgui](https://github.com/ocornut/imgui) gui library
- [imwindow](https://github.com/thennequin/ImWindow) window docking library for imgui
- [MetaStuff](https://github.com/eliasdaler/MetaStuff) serialization/deserialization/introspection stuff
- [spdlog](https://github.com/gabime/spdlog) Fast c++ logging library
