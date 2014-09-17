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
#include <iostream>


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
    std::ifstream in(filename);
    if(!in.is_open())
    {
        std::cout << "failed file open" << std::endl;
        return -1;
    }

    char buff[256];
    while(!in.eof())
    {
        in.getline(buff, 256);
        coord.push_back(new std::string(buff));
    }


    for (int i = 0; i < coord.size(); i++)
    {
        if(coord[i]->c_str()[0] == '#')
        {
            continue;
        }
        else if(coord[i]->c_str()[0] == 'v' && coord[i]->c_str()[1] == ' ')
        {

            float tmpx , tmpy , tmpz;
            sscanf(coord[i]->c_str(), "v %f %f %f " , &tmpx , &tmpy , &tmpz);
            vertex.push_back(new coordinate(tmpx , tmpy , tmpz));
        }
        else if(coord[i]->c_str()[0] == 'v' && coord[i]->c_str()[1] == 'n')
        {
            float tmpx , tmpy , tmpz;
            sscanf(coord[i]->c_str(), "vn %f %f %f " , &tmpx , &tmpy , &tmpz);
            normals.push_back(new coordinate(tmpx , tmpy , tmpz));
        }
        else if(coord[i]->c_str()[0] == 'f')
        {
            int a , b , c , d , e;
            if(count(coord[i]->begin(), coord[i]->end() , ' ') == 3)
            {
                sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d " , &a , &b , &c , &b , &d , &b);
                faces.push_back(new face(b,a,c,d));
            }
            else
            {
                sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d" , &a , &b , &c , &b , &d , &b , &e , &b);
                faces.push_back(new face(b,a,c,d,e));
            }
        }
    }

    //draw
    int num;
    num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    for(int i=0;i<faces.size();i++)
    {
        if(faces[i]->four)      //if it's a quad draw a quad
        {
            glBegin(GL_QUADS);
            //basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
            //I subtract 1 because the index start from 0 in C++
            glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
            //draw the faces
            glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
            glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
            glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
            glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
            glEnd();
        }
        else{
            glBegin(GL_TRIANGLES);
            glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
            glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
            glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
            glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
            glEnd();
        }
    }
    glEndList();

    //delete vectors
    for (int i = 0; i < coord.size(); ++i)
    {
        delete coord[i];
    }
    for (int i = 0; i < faces.size(); ++i)
    {
        delete faces[i];
    }
    for (int i = 0; i < normals.size(); ++i)
    {
        delete normals[i];
    }
    for (int i = 0; i < vertex.size(); ++i)
    {
        delete vertex[i];
    }
    return num;
}


int cube;

void init()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, 16/9, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    cube = loadObject("suzanne.obj");
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogf(GL_FOG_DENSITY, 0.6);
    /*glFogf(GL_FOG_START, 1.0);
    glFogf(GL_FOG_END, 5.0);*/
    float fogcol[] = {0.5 , 0.5 , 0.5 , 0.5};
    glFogfv(GL_FOG_COLOR, fogcol);
    float col[] = {1.0 , 1.0 , 1.0 , 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
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