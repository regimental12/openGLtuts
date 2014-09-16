#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>


struct coordinate{
    float x,y,z;
    coordinate(float a , float b , float c) : x(a) , y(b) , z(c) {};
};

struct face{
    int facenum;
    bool four;
    int faces[4];
    face(int facen , int f1 , int f2 , int f3) : facenum(facen){
        faces[0] = f1;
        faces[1] = f2;
        faces[2] = f3;
        four = false;
    }
    face(int facen , int f1 , int f2 , int f3 , int f4) : facenum(facen){
        faces[0] = f1;
        faces[1] = f2;
        faces[2] = f3;
        faces[3] = f4;
        four = true;
    }
};

float angle = 0.0;

int loadObject(const char* filename)
{
    std::vector<std::string*> coord;
    std::vector<coordinate*>  vertex;
    std::vector<face*>        faces;
    std::vector<coordinate*>  normals;
}




void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640/480, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
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
        cout << "Failed Window Init\n";
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
        if (1000/30 > (SDL_GetTicks()-start))
        {
            SDL_Delay(1000/30 > (SDL_GetTicks()-start));
        }
        if (angle > 360)
        {
            angle -= 360;
        }
        angle += 0.5;

    }
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}