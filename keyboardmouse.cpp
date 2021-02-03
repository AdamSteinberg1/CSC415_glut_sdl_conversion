#include "opengl.h"
#include "constants.h"
#include "prototypes.h"

extern float angularVelocityX;
extern float angularVelocityY;
extern float angularVelocityZ;
extern float angleX;
extern float angleY;
extern float angleZ;
extern float camPosX;
extern float camPosY;
extern float camPosZ;
extern int viewMode;

bool wireframeEnabled = false;
bool axisEnabled = true;
bool helloWorldEnabled = true;
int viewMode = 1;



void modifyVelocity(int x, int y, bool increase)
{
  const float delta = 0.5; //how much each click changes the angular velocity
  const float limit = 10;  //the maximum angular speed

  if(x<WINDOW_WIDTH/2) //left side
  {
    if(y > x) //top left corner
    {
      if(increase) //left click
      {
        angularVelocityY += delta;
        if(angularVelocityY > limit)
          angularVelocityY = limit;
      }
      else //right click
      {
        angularVelocityY -= delta;
        if(angularVelocityY < -limit)
          angularVelocityY = -limit;
      }
    }
    else //bottom
    {
      if(increase) //left click
      {
        angularVelocityZ += delta;
        if(angularVelocityZ > limit)
          angularVelocityZ = limit;
      }
      else //right click
      {
        angularVelocityZ -= delta;
        if(angularVelocityZ < -limit)
          angularVelocityZ = -limit;
      }
    }
  }
  else  //right side
  {
    if(y > WINDOW_HEIGHT - x) //top right corner
    {
      if(increase) //left click
      {
        angularVelocityX += delta;
        if(angularVelocityX > limit)
          angularVelocityX = limit;
      }
      else //right click
      {
        angularVelocityX -= delta;
        if(angularVelocityX < -limit)
          angularVelocityX = -limit;
      }
    }
    else //bottom
    {
      if(increase) //left click
      {
        angularVelocityZ += delta;
        if(angularVelocityZ > limit)
          angularVelocityZ = limit;
      }
      else //right click
      {
        angularVelocityZ -= delta;
        if(angularVelocityZ < -limit)
          angularVelocityZ = -limit;
      }
    }
  }
}


void handle_mouse_click(Uint32 button, Sint32 x, Sint32 y)
{
  // Handler for mouse interaction
      switch (button)
      {
          case SDL_BUTTON_LEFT:
              modifyVelocity(x,WINDOW_HEIGHT-y,true);
              break;


          case SDL_BUTTON_RIGHT:
              modifyVelocity(x,WINDOW_HEIGHT-y,false);
              break;
      }
}



void handle_key_down( SDL_keysym* keysym )
{
  //handler for key presses
    switch( keysym->sym )
    {
      case SDLK_ESCAPE: //quit
      case SDLK_q:
          quit_program( 0 );
          break;

      case SDLK_r:  //reset
        if(SDL_GetModState() & KMOD_SHIFT) //if shift is pressed i.e. capital 'R'
        {
          camPosX = 6.0;
          camPosY = 5.0;
          camPosZ = 3.0;
        }
        angleX = 0.0;
        angleY = 0.0;
        angleZ = 0.0;
      case SDLK_s:  //stop roation
        angularVelocityX = 0.0;
        angularVelocityY = 0.0;
        angularVelocityZ = 0.0;
        break;

      case SDLK_PAGEUP: //zoom in
        if(viewMode ==1)
        {
          camPosX *= 0.9;
          camPosY *= 0.9;
          camPosZ *= 0.9;
          changeProjection();
        }
        break;
      case SDLK_PAGEDOWN: //zoom out
        if(viewMode ==1)
        {
          camPosX *= 1.1;
          camPosY *= 1.1;
          camPosZ *= 1.1;
          changeProjection();
        }
        break;


      //The following keys are functions that used to be part of the menu

      //changing the projection
      case SDLK_1: //Perspective
        viewMode = 1;
        changeProjection();
        break;
      case SDLK_2: //Orthographic
        viewMode = 2;
        changeProjection();
        break;
      case SDLK_3: //Custom
        viewMode = 3;
        changeProjection();
        break;

      case SDLK_w: //wireframe
        wireframeEnabled = !wireframeEnabled;
        break;

      case SDLK_a: //axis
        axisEnabled = !axisEnabled;
        break;

      case SDLK_h: //Hello World on roof
        helloWorldEnabled = !helloWorldEnabled;
        break;


      default:
          break;
    }

}
