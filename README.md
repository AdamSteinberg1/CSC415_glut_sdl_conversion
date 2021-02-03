#### To compile and run the house project:
```
make
./house
```

#### To compile and run the SDL double-buffering example
```
gcc sdl_double_buffer.c -lSDL -lGL -lGLU -lm
./a.out
```

#### New controls for the house program
Because we are no longer using glut menus, several of the menu functions have been remapped to keys.  
  
1 => Change to perspective projection  
2 => Change to orthographic projection  
3 => Change to custom projection (values for this projection have to be specified in the command line)  
w => Toggles wireframe  
a => Toggles axes  
h => Toggles Hello World on roof  
