#include "gfx.h"

GLuint pixel_gfx_texture;
GLenum pixel_gfx_format;
GLsizei pixel_gfx_w;
GLsizei pixel_gfx_h;

char *pixel_gfx_init(GLsizei w, GLsizei h, GLenum format)
{
    // initialize global variables for rendering & updates
    pixel_gfx_format = format;
    pixel_gfx_w = w;
    pixel_gfx_h = h;

    // load the texture
    {
        glGenTextures( 1, &pixel_gfx_texture ); 
        glBindTexture( GL_TEXTURE_2D, pixel_gfx_texture ); 
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 

        //even better quality, but this will do for now.
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);

        //to the edge of our shape. 
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

        //Generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, 0);
    }

    // allocate buffer
    char *buffer = malloc(w * h * 4); // TODO don't hardcode for 4 bytes per pixel

    return buffer;
}

/**
 * Update the graphics buffer in video RAM.
 */
void pixel_gfx_update(const char *buffer, char r, char g, char b, char a)
{
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pixel_gfx_w, pixel_gfx_h, pixel_gfx_format, GL_UNSIGNED_BYTE, buffer);

    // initialize orthographic projection
    {
        // select the projection matrix and clear it out
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        // set up an orthographic projection with the same near clip plane
        glOrtho(-pixel_gfx_w/2, pixel_gfx_w/2, -pixel_gfx_h/2, pixel_gfx_h/2, 0, 100);

        // select modelview matrix and clear it out
        glMatrixMode(GL_MODELVIEW);
    }

    // do update
    {
        glClearColor (r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glEnable( GL_TEXTURE_2D );

        // render texture
        const int iw = pixel_gfx_w;
        const int ih = pixel_gfx_h;
        glTranslatef( -iw/2, -ih/2, 0 );
        glBegin(GL_QUADS);
            glTexCoord2i(0,0); glVertex2i(0, 0);
            glTexCoord2i(1,0); glVertex2i(iw, 0);
            glTexCoord2i(1,1); glVertex2i(iw, ih);
            glTexCoord2i(0,1); glVertex2i(0, ih);
        glEnd();
    }

    // end projection matrix
    {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
}

void pixel_gfx_end(const char *buffer)
{
    free(buffer);
}
