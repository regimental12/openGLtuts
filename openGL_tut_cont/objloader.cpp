#include "objloader.h"

coordinate::coordinate(float a,float b,float c)
{
    x=a;
    y=b;
    z=c;
}

face::face(int facen,int f1,int f2,int f3 , int t1,int t2,int t3,int m)
{
    facenum=facen;
    faces[0]=f1;
    faces[1]=f2;
    faces[2]=f3;
    texcoord[0]=t1;
    texcoord[1]=t2;
    texcoord[2]=t3;
    mat=m;
    four=false;
}

face::face(int facen,int f1,int f2,int f3,int f4,int t1,int t2,int t3,int t4,int m)
{
    facenum=facen;
    faces[0]=f1;
    faces[1]=f2;
    faces[2]=f3;
    faces[3]=f4;
    texcoord[0]=t1;
    texcoord[1]=t2;
    texcoord[2]=t3;
    texcoord[3]=t4;
    mat=m;
    four=true;
}

material::material(const char* na , float a , float b , float n , float ni2 , float* d , float* a , float* s , int i , int t)
{
    name = na;
    alpha = a;
    ns = n;
    ni = ni2;
    dif[0] = d[0];
    dif[1] = d[1];
    dif[2] = d[2];

    amb[0] = a[0];
    amb[1] = a[1];
    amb[2] = a[2];

    spec[0] = s[0];
    spec[1] = s[1];
    spec[2] = s[2];

    illum = i;
    texture = t;
}

textcoord::textcoord(float a, float b)
{
    u = a;
    v = b;
}

objloader::objloader()
{
}

objloader::~objloader()
{
}

int objloader::load(const char *filename)
{

    std::ifstream in(filename);
    if(!in.is_open())
    {
        std::cout << "failed file open" << std::endl;
        return -1;
    }

    char buff[256];
    int curmat;
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
            if(count(coord[i]->begin(), coord[i]->end() , ' ') == 4) //quad
            {
                if(coord[i]->find("//") != std::string::npos)
                {
                    sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d" , &a , &b , &c , &b , &d , &b , &e , &b);
                    faces.push_back(new face(b,a,c,d,e,0,0,0,0,curmat));
                }
                else if(coord[i]->find("/") != std::string::npos)
                {
                    int t[4];
                    sscanf(coord[i]->c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d  " , &a , &t[0] , &b , &c , &t[1] , &b , &d , &t[2] , &b , &e ,  &t[3] , &b);
                    faces.push_back(new face(b,a,c,d,e,t[0],t[1],t[2],t[3],curmat));

                }
                else
                {
                    sscanf(coord[i]->c_str(), "f %d %d %d %d" , &a , &b , &c , &d);
                    faces.push_back(new face(-1,a,b,c,d,0,0,0,0,curmat));
                }
            }
            else //triangle
            {
                if(coord[i]->find("//")!=std::string::npos)
                {
                    sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
                    faces.push_back(new face(b,a,c,d,0,0,0,curmat));
                }
                else if(coord[i]->find("/")!=std::string::npos)
                {
                    int t[3];
                    sscanf(coord[i]->c_str(),"f %d/%d/%d %d/%d/%d %d/%d/%d",&a,&t[0],&b,&c,&t[1],&b,&d,&t[2],&b);
                    faces.push_back(new face(b,a,c,d,t[0],t[1],t[2],curmat));
                }
                else
                {
                    sscanf(coord[i]->c_str(),"f %d %d %d",&a,&b,&c);
                    faces.push_back(new face(-1,a,b,c,0,0,0,curmat));
                }
            }
        }
        else
        {

        }
    }

    //draw
    int num;
    num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    for(int i=0;i<faces.size();i++)
    {
        if(faces[i]->four)
        {
            glBegin(GL_QUADS);

            glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
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
