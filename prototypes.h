#ifndef PROTOTYPES
#define PROTOTYPES

#include "structs.h"

void init(int width, int height);
void drawAxes(int length);
void defineHouse(face *faces);
void drawHouse(struct face *faces);
void drawHelloWorld();
void display(void);
void updateRotations(void);
void createMenus();
void drawText();
void changeProjection();
void handle_key_down( SDL_keysym* keysym );
void handle_mouse_click(Uint32 button, Sint32 x, Sint32 y);
void quit_program( int code );

#endif
