#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"

using namespace std;

float angle = 0.0;
const int trianlge = 1;

void drawCube(float size)
{
    float difamb[] = {1.0 , 0.5 , 0.3 , 1.0};
    glBegin(GL_QUADS);

    //front face
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);

    //left face
    glNormal3f(-1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(-size/2, -size/2, size/2);

    //back face
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(size/2, size/2, -size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(size/2, -size/2, -size/2);

    //right face
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(size/2, size/2, -size/2);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);
    glVertex3f(size/2, -size/2, -size/2);

    //top face
    glNormal3f(0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(size/2, size/2, -size/2);

    //bottom face
    glNormal3f(0.0, -1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(size/2, -size/2, size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(size/2, -size/2, -size/2);

    glEnd();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640/480, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    float dif[] = {1.0 , 1.0 , 1.0 , 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    float amb[] = {0.2 , 0.2, 0.2 , 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float pos[] = {-2.0 , 2.0 , -3.0 , 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    drawCube(1.0);
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