
#ifndef INIT
#define INIT

#include "opengl.h"
#include "prototypes.h"

void init(int width, int height)
{
  /* Our shading model--Flat. */
  glShadeModel( GL_FLAT );

  /* Set the clear color. */
  glClearColor( 0, 0, 0, 0 );

  /* Setup our viewport. */
  glViewport( 0, 0, width, height );

  /*
   * Change to the projection matrix and set
   * our viewing volume.
   */
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );

  changeProjection();
}

#endif
