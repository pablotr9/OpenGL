
#include <cstdlib>
#include "dependente\glew\glew.h"
#include "dependente\freeglut\freeglut.h"
#include "dependente\freeglut\glut.h" // Include GLFW
#include "dependente\glfw\glfw3.h" // Include GLM 
#include "dependente\glm\glm.hpp" 
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>





float angle = 0.0f;
float rotate = 0.0f;
float myscale = 0.0f;
float myTranslate = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;
float y = 1.0f;
float yy = 0.0f;
float deltaAngle = 0.0f;
float deltaMove = 0;
const float PI = 3.14159;
int action = 0;
int ccc = 0;
int crece = 0;
float updown = 0.0f;
float increaseupdown = 0.0f;

int num_tri = 0, num_square = 0, num_circle = 0, num_cube = 0;;
std::vector<float> triangles;
std::vector<float> squares;
std::vector<float> circles;
std::vector<float> cubes;

int triangleAmount = 290;

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
	if (y > 1.2f)
		increaseupdown -= 0.02f;
	else if (y < 0.8f)
		increaseupdown += 0.02f;
	
}


void computeDir(float deltaAngle) {

	angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
}
void computeY(float yk) {
	y += yk;
}
void computeUpDown(float upd) {

	increaseupdown += upd;
}


void updateView(){
	rotate += 0.5;

	if (action == 1) {
		if (ccc = 0) {
			myTranslate += 0.1;
		}
		if (myTranslate >= 5.0f) {
			ccc = 1;
		}
		if (ccc == 1) {
			myTranslate -= 0.1;
		}
		if (myTranslate <= -3.0f) {
			ccc = 0;
		}
	}

	if (crece == 1)
	myscale += 0.002;
	if (crece == 2)
	myscale -= 0.002;
	if (myscale >= 2.5f)
	crece = 2;
	if (myscale <= 0.01)
	crece = 1;
	if (rotate >= 360)
	rotate = 0;
	if (deltaMove)
	computePos(deltaMove);
	if (deltaAngle)
	computeDir(deltaAngle);
	if (updown)
	computeUpDown(updown);
	if (yy)
	computeY(yy);
}

void renderScene(void) {

	

	updateView();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(x, 1.0f, z, x + lx , y, z + lz, 0.0f, 1.0f, 0.0f);
	
	// Draw ground
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f+increaseupdown, -100.0f);
	glVertex3f(-100.0f, 0.0f+increaseupdown, 100.0f);
	glVertex3f(100.0f, 0.0f+increaseupdown, 100.0f);
	glVertex3f(100.0f, 0.0f+increaseupdown, -100.0f);
	glEnd();






	
	
	//draw 2d triangles
	for (int i = 0; i < num_tri; i+=2) {
		glPushMatrix();
		glColor3f(1, 0, 0);
		glTranslatef(triangles[i], 0.1f+increaseupdown, triangles[i+1]);
		glBegin(GL_TRIANGLES); 
		glVertex3f(-0.5f, 0.2f, -5.0f);
		glVertex3f(-1.0f, 1.0f, -5.0f);
		glVertex3f(-1.5f, 0.2f, -5.0f);
		glEnd();
		glPopMatrix();
	}

	//draw 2dsquare
	for (int i = 0; i < num_square; i += 2) {
		glPushMatrix();
		glColor3f(0.0, 1, 0.0);
		glTranslatef(squares[i], 0.75f + increaseupdown, squares[i + 1]);
		glBegin(GL_POLYGON);
		glVertex3f(2.0, 0.1 , 0.0);
		glVertex3f(6.0, 0.1 , 0.0);
		glVertex3f(6.0, 2 , 0.0);
		glVertex3f(2.0, 2, 0.0);
		glEnd();
		glFlush();
		glPopMatrix();
	}

	//draw 2d circle
	for (int i = 0; i < num_circle; i += 2) {
		glPushMatrix();
		glTranslatef(circles[i], 1 + increaseupdown, circles[i + 1]);
		glColor3f(0.2, 0.3, 0.5);
		glBegin(GL_POLYGON);
		for (double i = 0; i < 2 * PI; i += PI / 12) 
			glVertex3f(cos(i) * 1, sin(i) * 1 , 0.0);
		glEnd();
		glPopMatrix();
	}


	//draw 3d cube
	for (int i = 0; i < cubes.size(); i += 2) {
		glPushMatrix();
		glTranslatef(cubes[i], 2 + increaseupdown, cubes[i+1]);
		if (action == 1) 
			glTranslatef( myscale * 10, 0, 0);
		
		if(action == 2)
			glScalef(myscale, myscale, myscale);
		if (action == 3)
			glRotatef(rotate, 1,1, 0);

		if (action == 4) {
			glTranslatef(myscale * 10, 0, 0);
			glRotatef(rotate, 1, 1, 0);
			glScalef(myscale, myscale, myscale);

		}

		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, -0.5);   
		glColor3f(0.9, 0.0, 0.0);
		glVertex3f(0.5, -0.5, -0.5);
		glColor3f(0.9, 0.0, 0.0);
		glVertex3f(0.5, 0.5, -0.5);
		glColor3f(0.9, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, -0.5);
		glColor3f(0.8, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, -0.5);  

		glEnd();
		glBegin(GL_POLYGON);		
		glColor3f(0.8, 0.0, 0.0);
		glVertex3f(0.5, -0.5, 0.5);
		glColor3f(0.7, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.5);
		glColor3f(0.7, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.5);
		glColor3f(0.6, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.5);
		glEnd();

		
		glBegin(GL_POLYGON);
		glColor3f(0.6, 0.0, 0.0);
		glVertex3f(0.5, -0.5, -0.5);
		glColor3f(0.5, 0.0, 0.0);
		glVertex3f(0.5, 0.5, -0.5);
		glColor3f(0.4, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.5);
		glColor3f(0.4, 0.0, 0.0);
		glVertex3f(0.5, -0.5, 0.5);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.4, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.5);
		glColor3f(0.4, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.5);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, -0.5);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.5);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(0.5, 0.5, -0.5);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, -0.5);
		glColor3f(0.2, 0.0, 0.0);
		glVertex3f(-0.5, 0.5, 0.5);
		glEnd();

		
		glBegin(GL_POLYGON);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(0.5, -0.5, -0.5);
		glColor3f(0.2, 0.0, 0.0);
		glVertex3f(0.5, -0.5, 0.5);
		glColor3f(0.3, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0.5);
		glColor3f(0.2, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, -0.5);
		glEnd();

		glFlush();
		glPopMatrix();
	}

	glutSwapBuffers();
}


void pressKey(unsigned char key, int xx, int yy) {

	switch (key) {
	case 'a': deltaAngle = -0.004f; break;
	case 'd': deltaAngle = 0.004f; break;
	case 'w': deltaMove = 0.3f; break;
	case 's': deltaMove = -0.3f; break;
	case 'o': { num_tri += 2;
		float r3 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		float r2 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		triangles.push_back(r3);
		triangles.push_back(r2-40);
		break;
	}	
	case 'i': {
		num_square+=2;
		float r3 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		float r2 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		squares.push_back(r3);
		squares.push_back(r2-40);
		break;
	}
	case 'p': {
		num_circle+=2;
		float r3 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		float r2 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		circles.push_back(r3);
		circles.push_back(r2-40);
		break;
	}
	case 'c': {
		num_cube += 2;
		float r3 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		float r2 = -40.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (40.0f - -40.0f)));
		cubes.push_back(r3);
		cubes.push_back(r2 - 40);
		break;
	}

	case 'm': {
		action = 1;
		myscale = 1;
		break;
	}case 'n': {
		action = 2;
		break;
	}
	case 'b': {
		action = 3;
		break;
	}
	case 'l': {
		if (action == 0)
			action = 4;
		else
			action = 0;
		break;
	}

	case 'e': updown += 0.06; break;
	case ' ': updown -= 0.06; break;
			  
	}
}

void releaseKey(unsigned char key, int x, int y) {

	switch (key) {
	case 'a':
	case 'd': deltaAngle = 0.0f; break;
	case 'w':
	case 's': deltaMove = 0; break;
	case ' ': updown = 0; break;
	case 'e': updown = 0; break;
	}
}

void releaseKey2(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP: yy = 0; break;
	case GLUT_KEY_DOWN: yy = 0; break;
	case GLUT_KEY_LEFT: deltaAngle = 0; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0; break;
	}
}

void specialKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP: yy += 0.003; break;
	case GLUT_KEY_DOWN: yy -= 0.003; break;
	case GLUT_KEY_LEFT: deltaAngle = -0.004f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.004f; break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Hw-2");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutKeyboardFunc(pressKey);
	glutSpecialFunc(specialKey);

	glutSpecialUpFunc(releaseKey2);

	glutIgnoreKeyRepeat(1);
	glutKeyboardUpFunc(releaseKey);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 1;
}
