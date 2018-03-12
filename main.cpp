
//Name: Mohit Punia
// Project 3
//Date: 11/02/2017
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159
#include <stdlib.h>
#include <iostream>

#include <math.h>
using namespace std;

int t;
bool Flag=false;

GLfloat MatrixXp[16];

GLfloat w,x,y,z,xl;
int xa,ya,za;
float Vertices[8][3]= {
                        0.0, 0.0, 0.0,
                        0.0, 0.0, 1.0,
                        0.0, 1.0, 0.0,
                        0.0, 1.0, 1.0,
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 1.0,
                        1.0, 1.0, 0.0,
                        1.0, 1.0, 1.0
                        };
float Normals[6][3] = {
                       0.0, 0.0, 1.0,
                        0.0, 0.0, -1.0,
                        0.0, 1.0, 0.0,
                        0.0, -1.0, 0.0,
                        1.0, 0.0, 0.0,
                        -1.0, 0.0, 0.0
                        };
int ind[12][6] ={ // vertices/normals
                    1,2, 7,2, 5,2,
                    1,2, 3,2, 7,2,
                    1,6, 4,6, 3,6,
                    1,6, 2,6, 4,6,
                    3,3, 8,3, 7,3,
                    3,3, 4,3, 8,3,
                    5,5, 7,5, 8,5,
                    5,5, 8,5, 6,5,
                    1,4, 5,4, 6,4,
                    1,4, 6,4, 2,4,
                    2,1, 6,1, 8,1,
                    2,1, 8,1, 4,1
                    };
int indverx,indvery,indverz,indnormx,indnormy,indnormz;
static void init(void);

//static GLint RotateY=0; /* model rotation Y index*/
static GLint RotateXm=0; /* model rotation X index*/


/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
            glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
          glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,1,0.1f, 100.0f);
 }

void CreateFromAxisAngle(GLfloat X, GLfloat Y, GLfloat Z, GLfloat degree)
{
 /* First we want to convert the degrees to radians since the angle is assumed to be in radians*/
GLfloat angle = (GLfloat)((degree / 180.0f) * PI);
 /* Here we calculate the sin( theta / 2) once for optimization */
GLfloat result = (GLfloat)sin( angle / 2.0f );
 /* Calcualte the w value by cos( theta / 2 ) */
w = (GLfloat)cos( angle / 2.0f );
 /* Calculate the x, y and z of the quaternion */
x = (GLfloat)(X * result);
y = (GLfloat)(Y * result);
z = (GLfloat)(Z * result);
}

void CreateMatrix(GLfloat *pMatrix)
 {
     // First row
    pMatrix[ 0] = 1.0f - 2.0f * ( y * y + z * z );
    pMatrix[ 1] = 2.0f * (x * y - z * w);
    pMatrix[ 2] = 2.0f * (x * z + y * w);
    pMatrix[ 3] = 0.0f;

    // Second row
    pMatrix[ 4] = 2.0f * ( x * y + z * w );
    pMatrix[ 5] = 1.0f - 2.0f * ( x * x + z * z );
    pMatrix[ 6] = 2.0f * (z * y - x * w );
    pMatrix[ 7] = 0.0f;

    //third row
    pMatrix[8]=2.0f*(x*z-y*w);
    pMatrix[9]=2.0f*(y*z+x*w);
    pMatrix[10]=1.0f-2.0f*(x*x+y*y);
    pMatrix[ 11] = 0.0f;

    pMatrix[ 12] = 0.0f;
    pMatrix[ 13] = 0.0f;
    pMatrix[ 14] = 0.0f;
    pMatrix[ 15] = 1.0f;

 }




static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-0.5f,-0.5f,-0.5f);

    glPushMatrix();
    glTranslatef(-0.5f,-0.5f,xl);
    gluLookAt(0,0,0,0.0,0.0,0.0,0.0,1.0,0.0);

    // your code here

    if (Flag==true)
    {


         RotateXm=(RotateXm+6)%360;
         // t=glutGet(GLUT_ELAPSED_TIME);

    }


  CreateMatrix(MatrixXp);
  CreateFromAxisAngle(xa,ya,za,RotateXm);
  glMultMatrixf(MatrixXp);


    for(int i=0;i<12;i++)
    {
        indverx=ind[i][0];
        indnormx=ind[i][1];
        indvery=ind[i][2];
        indnormy=ind[i][3];
        indverz=ind[i][4];
        indnormz=ind[i][5];
    glBegin(GL_TRIANGLES);
    {
    glColor3f(Vertices[indverx-1][0],Vertices[indverx-1][1],Vertices[indverx-1][2]);
    glNormal3f(Normals[indnormx-1][0],Normals[indnormx-1][1],Normals[indnormx-1][2]);
    glVertex3f(Vertices[indverx-1][0],Vertices[indverx-1][1],Vertices[indverx-1][2]);
    glColor3f(Vertices[indvery-1][0],Vertices[indvery-1][1],Vertices[indvery-1][2]);
    glNormal3f(Normals[indnormy-1][0],Normals[indnormy-1][1],Normals[indnormy-1][2]);
    glVertex3f(Vertices[indvery-1][0],Vertices[indvery-1][1],Vertices[indvery-1][2]);
    glColor3f(Vertices[indverz-1][0],Vertices[indverz-1][1],Vertices[indverz-1][2]);
    glNormal3f(Normals[indnormz-1][0],Normals[indnormz-1][1],Normals[indnormz-1][2]);
    glVertex3f(Vertices[indverz-1][0],Vertices[indverz-1][1],Vertices[indverz-1][2]);
    glEnd();
    }}
    glPopMatrix();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'd':
            xa=0;
            ya=0;
            za=1;
        RotateXm+=5;
            break;
        case 'a':
            xa=0;
            ya=0;
            za=1;
        RotateXm-=5;
	       break;
    }
}


void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        //Flag = true;
        Flag==true;
        xa=1;
        ya=0;
        za=0;
        RotateXm+=5;
    break;
    case GLUT_KEY_DOWN:
        //Flag = true;
        Flag==true;
        xa=1;
        ya=0;
        za=0;
        RotateXm-=5;
    break;
     case GLUT_KEY_LEFT:
        //Flag = true;
        Flag==true;
        xa=0;
        ya=1;
        za=0;
        RotateXm+=5;
    break;
     case GLUT_KEY_RIGHT:
        //Flag = true;
        Flag==true;
        xa=0;
        ya=1;
        RotateXm-=5;
    break;
    case GLUT_KEY_HOME:
        xl+=1;
    break;
    case GLUT_KEY_END:
        xl-=1;;
    break;
    }

  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(1200,650);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
