#ifndef PIXEL_GFX_H
#define PIXEL_GFX_H

#include <GL/gl.h>

/**
 * Initialize graphics buffer & OpenGL.
 *
 * Params:
 *  w and h are the buffer/texture width & height
 *  format is the buffer's color format (probably either GL_RGB or GL_RGBA)
 *
 * Returned value is an allocated array of raw pixel data (in the format
 * specified). Note that each color is multiple bytes (depending on each
 * channel) - for example, for GL_RGB each color consists of 3 consecutive
 * bytes for each red, green, and blue color value. These values are
 * consecutive from the upper left corner of the screen to the bottom right.
 * You can either update this raw data directly (and then pass to the buffer to
 * the pixel_gfx_update function), or you can use the utility function
 * "pixel_gfx_color" (followed by the pixel_gfx_update call).
 */
char *pixel_gfx_init(GLsizei w, GLsizei h, GLenum format);

/**
 * Update the graphics buffer in video RAM.
 *
 * Params:
 *  first param is the pixel buffer to actually render via OpenGL
 *  the rest are background RGB values from 0-255.
 */
void pixel_gfx_update(const char *buffer, char bg_r, char bg_g, char bg_b, char bg_a);

/**
 * Cleanup and free the buffer.
 */
void pixel_gfx_end(const char *buffer);

#endif
