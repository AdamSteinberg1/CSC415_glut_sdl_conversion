#ifndef MAIN
#define MAIN

#include "opengl.h"
#include "structs.h"
#include "prototypes.h"
#include "constants.h"


void quit_program( int code )
{
    /*
     * Quit SDL so we can release the fullscreen
     * mode and restore the previous video settings,
     * etc.
     */
    SDL_Quit( );

    /* Exit program. */
    exit( code );
}

void process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;

    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {

        switch( event.type ) {
        case SDL_KEYDOWN:
            /* Handle key presses. */
            handle_key_down( &event.key.keysym );
            break;
        case SDL_MOUSEBUTTONDOWN:
            /* Handle mouse click*/
            handle_mouse_click(event.button.button, event.button.x, event.button.y);
            break;
        case SDL_QUIT:
            /* Handle quit requests (like Ctrl-c). */
            quit_program( 0 );
            break;
        }
    }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv); //still needed for text

   /* Information about the current video settings. */
   const SDL_VideoInfo* info = NULL;
   /* Color depth in bits of our window. */
   int bpp = 0;
   /* Flags we will pass into SDL_SetVideoMode. */
   int flags = 0;

   /* First, initialize SDL's video subsystem. */
   if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
       /* Failed, exit. */
       fprintf( stderr, "Video initialization failed: %s\n",
            SDL_GetError( ) );
       quit_program( 1 );
   }

   /* Let's get some video information. */
   info = SDL_GetVideoInfo( );

   if( !info ) {
       /* This should probably never happen. */
       fprintf( stderr, "Video query failed: %s\n",
            SDL_GetError( ) );
       quit_program( 1 );
   }

   /*
    * We get the bpp we will request from
    * the display. On X11, VidMode can't change
    * resolution, so this is probably being overly
    * safe. Under Win32, ChangeDisplaySettings
    * can change the bpp.
    */
   bpp = info->vfmt->BitsPerPixel;

   /*
    * Now, we want to setup our requested
    * window attributes for our OpenGL window.
    * We want *at least* 5 bits of red, green
    * and blue. We also want at least a 16-bit
    * depth buffer.
    *
    * The last thing we do is request a double
    * buffered window. '1' turns on double
    * buffering, '0' turns it off.
    *
    * Note that we do not use SDL_DOUBLEBUF in
    * the flags to SDL_SetVideoMode. That does
    * not affect the GL attribute state, only
    * the standard 2D blitting setup.
    */
   SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); //enables double buffering

   /*
    * We want to request that SDL provide us
    * with an OpenGL window, in a windowed
    * video mode.
    */
   flags = SDL_OPENGL | SDL_RESIZABLE;

   /*
    * Set the video mode
    */
   if( SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, bpp, flags ) == 0 ) {
       /*
        * This could happen for a variety of reasons,
        * including DISPLAY not being set, the specified
        * resolution not being available, etc.
        */
       fprintf( stderr, "Video mode set failed: %s\n",
            SDL_GetError( ) );
       quit_program( 1 );
   }

   /*
    * At this point, we should have a properly setup
    * double-buffered window for use with OpenGL.
    */
   init( WINDOW_WIDTH, WINDOW_HEIGHT );

   /*
   glutMainLoop is replaced with an infinite while loop
   There are no callback functions anymore
   */
   while(1)
   {
     process_events();  //process input
     display();         //put frame on the screen
     updateRotations(); //change properties of the house (angle and angular velocity)
   }
   return 0; //the program never actually gets here
}

#endif
