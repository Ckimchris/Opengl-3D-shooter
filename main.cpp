
#include <cmath>			//sine and cosine functions
#include <windows.h>
#include <vector>
#include "camera.h"
#include <GL/glut.h>		//includes gl.h and glu.h
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>

#define PI 3.1415265359

static GLfloat MatSpec[] = {1.0,1.0,1.0,1.0};
static GLfloat MatShininess[] = {45.0};
static GLfloat LightPos[] = {-5, 5, 5.0,0.0};
static GLfloat ModelAmb[] = {0.5,0.5,0.5,0.0};


GLfloat ballRadius = 0.5f;   // Radius of the bouncing ball
GLfloat xPos = 4.0f;         // Ball's (x, y) position
GLfloat zPos = 1.0f;
GLfloat xPosMax, xPosMin, zPosMax, zPosMin; // Ball's (x, y) bounds
GLdouble xLeft, xRight, zBottom, zTop;      // Projection clipping area
GLfloat xSpeed = 0.02f;      // Ball's speed in x and y directions
GLfloat zSpeed = 0.002f;

int refreshMillis = 30;      // Refresh period in milliseconds

CCamera Camera;

float move = 0;

double C_angle;

double C_Radius;

double C_increment;

double eyex, eyey, eyez; 

double centerx, centery, centerz; 
	
double upx, upy, upz;

float S = .5;
float R = 1;

char axis;

int menu;


bool k = true, l = false;


void myCircle(float a, float b, float d, float e, int numPoints) 
//it will draw line segments to connect numPoints points on the circle to approximate a circle centered at the (x,y,z) and with the radius r on the plane z = z. 
//Then modify the display function to generate the circles in step 3 by calling this function, replacing the previous code from Step 2 and Step 3.
{

	glBegin(GL_LINE_LOOP);
	for(int i=0; i < 360; i++)
	{
		glVertex3f(e*cos(a * 3.14159 * i/numPoints), e*sin(b * 3.14159 * i/numPoints), d);
	}

	glEnd();
}

void moveCamera()
{	
	if (l == true)
    {
        upx = 0;
        upy = cos(C_angle + PI/2);
        upz = sin(C_angle + PI/2);
        eyex = 0;
        eyey = C_Radius*cos(C_angle);
        eyez = C_Radius*sin(C_angle);
    }

	if (k == true)
    {
        upx = -1.0;
        upy = -5;
        upz = -17.0;
        eyex = 0;
        eyey = 0;
        eyez = -1.0;  
    }
	glutPostRedisplay();
}

class bullet{
    static bullet Container;
};



void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	Camera.Render();
	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	glTranslatef(-5.0,0.0,0.0);
	glRotatef(90.0f, 0.0f, 1.0,0.0);

	glPushMatrix();
	glTranslatef(2, .25, 5.0 + move);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.2, 0.5, 0.8);
	glutSolidCube(.5);
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_LINES);
	for(int i=0;i<=10;i++) {
    if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
    glVertex3f(i,0,0);
    glVertex3f(i,0,10);
    if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
    glVertex3f(0,0,i);
    glVertex3f(10,0,i);
	};
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glBegin(GL_LINES);
	for(int i=0;i<=10;i++) {
    if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
    glVertex3f(i,0,0);
    glVertex3f(i,0,10);
    if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
    glVertex3f(0,0,i);
    glVertex3f(10,0,i);
	};
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,2.0,0.0);
	glBegin(GL_LINES);
	for(int i=0;i<=10;i++) {
    if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
    glVertex3f(i,0,0);
    glVertex3f(i,0,10);
    if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
    glVertex3f(0,0,i);
    glVertex3f(10,0,i);
	};
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0,2.0,0.0);
	glBegin(GL_LINES);
	for(int i=0;i<=10;i++) {
    if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
    glVertex3f(i,0,0);
    glVertex3f(i,0,10);
    if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
    glVertex3f(0,0,i);
    glVertex3f(10,0,i);
	};
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, 0, zPos);  // Translate to (xPos, yPos)
	glRotatef(90.0f, 0.0f, 1.0,0.0);
	glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0f, 0.0f, 1.0f);  // Blue
      glVertex2f(0.0f, 0.0f);       // Center of circle
      int numSegments = 100;
      GLfloat angle;
      for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
         angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
         glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
      }
   glEnd();

	glPopMatrix();

	glFlush();			//Finish rendering
	glutSwapBuffers();	//Swap the buffers ->make the result of rendering visible
	
	 xPos += xSpeed;
	 zPos += zSpeed;
   // Check if the ball exceeds the edges
	 if (xPos > 10.0) {
      xPos = xPosMax;
      xSpeed = -xSpeed;
   } else if (xPos < 0) {
      xPos = xPosMin;
      xSpeed = -xSpeed;
   }
   if (zPos > 10.0) {
      zPos = zPosMax;
      zSpeed = -zSpeed;
   } else if (zPos < 0) {
      zPos = zPosMin;
      zSpeed = -zSpeed;
   }
}

void initCameraSetting()
{	

//The following variable records the current angle between the vector (1,0,0) and (eyex, eyey, eyez)
	C_angle = 0;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the radius of the camera's orbit
	C_Radius = 20;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the rotation speed of the camera
	C_increment = S*PI / (360*2);

//Recording the currnet position of the camera.
	eyex = 0; eyey = 0; eyez = C_Radius;//C_Radius;

//Specifies the position of the point looked at as (0,0,0).
	centerx = 0; centery = 0; centerz=0;

//Specifies the direction of the up vector. 
	upx = 0; upy=1;  upz=0;


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);

	glMatrixMode (GL_PROJECTION);


}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,1.0,200.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  
}


void KeyDown(unsigned char key, int x, int y)
{	
	switch(key)
	{
	case 27:	//ESC
		exit(0);
		break;
	case 'a':		
		Camera.RotateY(5.0);
		Display();
		break;
	case 'd':		
		Camera.RotateY(-5.0);
		Display();
		break;
	case 'w':		
		Camera.MoveForwards( -0.3 ) ;
		Display();
		break;
	case 's':		
		Camera.MoveForwards( 0.3 ) ;
		Display();
		break;
	case 'k':		
		Camera.Fix();
		Display();
		break;
	case 'l':		
		Camera.Fix1();
		Camera.RotateY(-90.0);
		Display();
		break;
	case 'x':		
		Camera.RotateX(5.0);
		Display();
		break;
	case 'y':		
		Camera.RotateX(-5.0);
		Display();
		break;
	case 'c':		
		if(move > -4.8)
		{
		Camera.StrafeRight(-0.3);
		move += -.3;
		Display();
		}
		break;
	case 'v':	
		if(move < 4.6)
		{
		Camera.StrafeRight(0.3);
		move += .3;
		Display();
		}
		break;
	case 'f':
		Camera.Move(F3dVector(0.0,-0.3,0.0));
		Display();
		break;
	case 'r':
		Camera.Move(F3dVector(0.0,0.3,0.0));
		Display();
		break;

	
	}
}

int main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300,300);
	glutCreateWindow("RPG");
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glClearColor(0.0,0.0,0.0,0.0);
	initCameraSetting();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyDown);
	glutIdleFunc(moveCamera);
	Camera.Move(F3dVector(0.0,5.0,20.0));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ModelAmb);
	glutMainLoop();
	return 0;
}
