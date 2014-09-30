#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "objloader.h"

float angle = 0.0;
int cube;



void init()
{
    objloader* obj = new objloader();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 16/9, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    cube = obj->load("suzanne.obj");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float col[] = {1.0 , 1.0 , 1.0 , 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
    std::cout << glGetString(GL_VENDOR)<< "\n" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float pos[] = {-1.0,1.0,-2.0,1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 0.5);
    glCallList(cube);
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    bool running = true;
    int start ;
    SDL_Event event;


    window = SDL_CreateWindow("openGL", 0, 0, 640, 480, SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    if (window == NULL)
    {
        std::cout << "Failed Window Init\n";
    }
    init();
    while (running)
    {
        start = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        display();
        SDL_GL_SwapWindow(window);
        if (angle > 360)
        {
            angle -= 360;
        }
        angle += 0.5;
        if (1000/30 > (SDL_GetTicks()-start))
        {
            SDL_Delay(1000/30 > (SDL_GetTicks()-start));
        }


    }

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}