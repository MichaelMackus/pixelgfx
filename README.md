# pixelgfx - simple pixel graphics library

This library is meant for games that deal with pixel graphics and want to
efficiently display graphics on the screen. The library has a simple OpenGL
binding that should work on most OpenGL implementations (tested on as early as
an OpenGL 2.1 laptop). The performance should be quite good compared to
something like using software and/or SDL for graphics.

The API is very simple (hence the name) and currently mainly supports direct
writing to a pixel frame buffer.

Currently the library is written in native C.
