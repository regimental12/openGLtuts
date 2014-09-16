#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"


using namespace std;

float angle = 0.0;
const int trianlge = 1;

unsigned int loadTexture(const char* filename)
{
    SDL_Surface* img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    return id;
}

unsigned int tex;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640/480, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    tex = loadTexture("Brickwall.bmp");
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
        glVertex3f(-2.0, 2.0, 0.0);
    glTexCoord2f(0.0, 0.0);
        glVertex3f(-2.0, -2.0, 0.0);
    glTexCoord2f(1.0, 0.0);
        glVertex3f(2.0, -2.0, 0.0);
    glTexCoord2f(1.0, 1.0);
        glVertex3f(2.0, 2.0, 0.0);
    glEnd();
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