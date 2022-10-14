//Isaac Fowler
//Added joints, multiple instances, and camera movement with arrow keys to simulate walking through scene
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string>
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600

//Joints
static int shoulderAngle = 0, elbowAngle = 0;
static int leftHipAngle = 0, rightHipAngle;
static int kneeAngle = 0;

bool solid = true;
bool clearScreen = false;
bool displayModel = true;
bool displayAxis = true;
bool perspective = true;
int Xrotation = 0;
int Yrotation = 0;
int Zrotation = 0;
std::string Color = "blue";
std::string prevColor;
bool BlackAndWhite = false;
float zCamera = 4.5;
float xCamera = 0.0;
float lxCamera = 0.0;
float lzCamera = -1.0;
float cameraAngle = 0.0;
int model = 1;

void setColor();

static void drawAxes() {
	glBegin(GL_LINES);
	if (BlackAndWhite == true) {
		glColor3f(1, 1, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
	}
	else {
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
	}
	glEnd();
}

static void drawRobot(int arg) {
	//drawRobot(1) is solid and (2) is wireframe

	glRotatef(Xrotation, 1.0, 0.0, 0.0);
	glRotatef(Yrotation, 0.0, 1.0, 0.0);
	glRotatef(Zrotation, 0.0, 0.0, 1.0);

	//Body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1.5, 1);
	if (arg == 1)
		glutSolidCube(1.0);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Head
	glPushMatrix();
	glTranslatef(0, 1.24, 0);
	if (arg == 1)
		glutSolidSphere(0.5f, 50, 50);
	else if (arg == 2)
		glutWireSphere(0.5f, 50, 50);
	glPopMatrix();

	//Right arm
	//Upper
	glPushMatrix();
	glTranslatef(0.5, 0.4, 0);
	glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.25, 0, 0);
	glScalef(0.5, 0.35, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0.5, 0, 0);
	glRotatef(-(GLfloat)elbowAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.5, 0, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Left arm
	//Upper
	glPushMatrix();
	glTranslatef(-0.5, 0.4, 0);
	glRotatef(-(GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
	glTranslatef(-0.25, 0, 0);
	glScalef(0.5, 0.35, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(-0.5, 0, 0);
	glRotatef((GLfloat)elbowAngle, 0.0, 1.0, 0.0);
	glTranslatef(-0.5, 0, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Right leg
	//Upper
	glPushMatrix();
	glTranslatef(0.3, -0.75, 0);
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.25, 0);
	glScalef(0.35, 0.5, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0, -0.5, 0);
	glRotatef((GLfloat)kneeAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.5, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Left leg
	//Upper
	glPushMatrix();
	glTranslatef(-0.3, -0.75, 0);
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.25, 0);
	glScalef(0.35, 0.5, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0, -0.5, 0);
	glRotatef((GLfloat)kneeAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.5, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();
}

static void drawPig(int arg) {

	glRotatef(Xrotation, 1.0, 0.0, 0.0);
	glRotatef(Yrotation, 0.0, 1.0, 0.0);
	glRotatef(Zrotation, 0.0, 0.0, 1.0);
	glTranslatef(0, -0.75, 0);

	//Body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1.25, 1, 2);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Head
	glPushMatrix();
	glTranslatef(0, 0.25, 1.25);
	glScalef(1, 1, 1);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Nose
	glPushMatrix();
	glTranslatef(0, 0, 1.8125);
	glScalef(0.5, 0.375, 0.125);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Front Left Leg
	glPushMatrix();
	//glTranslatef(0.375, -0.875, 0.625);
	glTranslatef(0.375, -0.5, 0.625);
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.375, 0);
	glScalef(0.5, 0.75, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Front Right Leg
	glPushMatrix();
	glTranslatef(-0.375, -0.5, 0.625);
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.375, 0);
	glScalef(0.5, 0.75, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Back Left Leg
	glPushMatrix();
	glTranslatef(0.375, -0.5, -0.875);
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.375, 0);
	glScalef(0.5, 0.75, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Back Right Leg
	glPushMatrix();
	glTranslatef(-0.375, -0.5, -0.875);
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.375, 0);
	glScalef(0.5, 0.75, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	glColor3d(0.2, 0.2, 0.2);

	//Left Eye
	glPushMatrix();
	glTranslatef(-0.4375, 0.265, 1.75);
	glScalef(1, 1, 0);
	glutSolidCube(0.125f);
	glPopMatrix();

	//Right Eye
	glPushMatrix();
	glTranslatef(0.4375, 0.265, 1.75);
	glScalef(1, 1, 0);
	glutSolidCube(0.125f);
	glPopMatrix();

	glColor3d(1, 1, 1);

	//Left Pupil
	glPushMatrix();
	glTranslatef(-0.325, 0.265, 1.75);
	glScalef(1, 1, 0);
	glutSolidCube(0.125f);
	glPopMatrix();

	//Right Pupil
	glPushMatrix();
	glTranslatef(0.325, 0.265, 1.75);
	glScalef(1, 1, 0);
	glutSolidCube(0.125f);
	glPopMatrix();

	setColor();
}

static void drawCreeper(int arg) {

	glRotatef(Xrotation, 1.0, 0.0, 0.0);
	glRotatef(Yrotation, 0.0, 1.0, 0.0);
	glRotatef(Zrotation, 0.0, 0.0, 1.0);

	//glColor3ub(0, 0, 255);
	//Body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1.5, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Head
	glPushMatrix();
	glTranslatef(0, 1.25, 0);
	glScalef(1, 1, 1);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Front Left Leg
	glPushMatrix();
	glTranslatef(-0.25, -0.75, 0.25);
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.33, 0.25);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Front Right Leg
	glPushMatrix();
	glTranslatef(0.25, -0.75, 0.25);
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.33, 0.25);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Back Left Leg
	glPushMatrix();
	glTranslatef(-0.25, -0.75, -0.25);
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.33, -0.25);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Back Right Leg
	glPushMatrix();
	glTranslatef(0.25, -0.75, -0.25);
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.33, -0.25);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	glColor3d(0.2, 0.2, 0.2);

	//Left Eye
	glPushMatrix();
	glTranslatef(-0.25, 1.383, 0.5);
	glScalef(1, 1, 0);
	glutSolidCube(0.25f);
	glPopMatrix();
	
	//Right Eye
	glPushMatrix();
	glTranslatef(0.25, 1.383, 0.5);
	glScalef(1, 1, 0.1);
	glutSolidCube(0.25f);
	glPopMatrix();

	//Mouth
	//Have to make each section a different polgyon because GL_POLYGON can't do concave shapes.
	glPushMatrix();
	glTranslatef(0, 1, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-0.125, 0.25, 0);
	glVertex3f(0.125, 0.25, 0);
	glVertex3f(0.125, -0.125, 0);
	glVertex3f(-0.125, -0.125, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.125, 0.125, 0);
	glVertex3f(0.25, 0.125, 0);
	glVertex3f(0.25, -0.25, 0);
	glVertex3f(0.125, -0.25, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 0.125, 0);
	glVertex3f(-0.125, 0.125, 0);
	glVertex3f(-0.125, -0.25, 0);
	glVertex3f(-0.25, -0.25, 0);
	glEnd();
	glPopMatrix();

	setColor();
	
}

void setColor() {
	if (Color == "red") {
		glColor3d(1, 0.2, 0);
	}
	else if (Color == "yellow") {
		glColor3d(1, 1, 0);
	}
	else if (Color == "blue") {
		glColor3d(0, 0.4, 1);
	}
	else if (Color == "green") {
		glColor3d(0.1, 1, 0.3);
	}
	else if (Color == "white") {
		glColor3d(1, 1, 1);
	}
}

// Handles the reshape event by setting the viewport so t aht it takes up the
// whole visible region, then sets the projection matrix to something
// reasonable that maintains proper aspect ratio.
void reshape(GLint w, GLint h)
{
	glViewport(9, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
}

/*
void mouseClick(int button, int state, int mousex, int mousey)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (Color == "white") {
			Color = prevColor;
		}
		else {
			prevColor = Color;
			Color = "white";
		}
		BlackAndWhite = !BlackAndWhite;
	}
	if (button == 3 && zCamera > 0.2)
		zCamera -= 0.1;
	else if (button == 4)
		zCamera += 0.1;
	glutPostRedisplay();
}
*/

void procKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': // Wireframe
		solid = false;
		break;

	case '2': // Solid
		solid = true;
		break;

	case 'c': // Clear screen
		clearScreen = !clearScreen;
		break;

	case 'm': // Toggle model view
		displayModel = !displayModel;
		break;

	case '3': //Toggle axis view
		displayAxis = !displayAxis;
		break;

	case '4': //Bend elbow
		(elbowAngle += 5) %= 360;
		break;

	case '5': //Raise shoulder
		(shoulderAngle += 5) %= 360;
		break;

	case '6': //Move Leg backwards
		(leftHipAngle += 5) %= 360;
		(rightHipAngle += 5) %= 360;
		break;

	case '7': //Bend Knee
		(kneeAngle += 5) %= 360;
		break;

	case '8': //Move left leg backwards
		(leftHipAngle += 5) %= 360;
		break;

	case '9': //Move right leg backwards
		(rightHipAngle += 5) %= 360;
		break;

	case 27:
		exit(0);
		break;
	}
}

void specialKeys(int key, int x, int y)
{
	float fraction = 0.1f;
	switch (key) {

	case GLUT_KEY_F4: //extend elbow
		(elbowAngle -= 5) %= 360;
		break;

	case GLUT_KEY_F5: //lower shoulder
		(shoulderAngle -= 5) %= 360;
		break;

	case GLUT_KEY_F6: //Move leg forward
		(leftHipAngle -= 5) %= 360;
		(rightHipAngle -= 5) % 360;
		break;

	case GLUT_KEY_F7: //Extend knee
		(kneeAngle -= 5) %= 360;
		break;

	case GLUT_KEY_F8: //Move left leg forward
		(leftHipAngle -= 5) %= 360;
		break;

	case GLUT_KEY_F9: //Move right leg forward
		(rightHipAngle -= 5) %= 360;
		break;

	case GLUT_KEY_LEFT:
		//xCamera -= 0.1;
		cameraAngle -= 0.01f;
		lxCamera = sin(cameraAngle);
		lzCamera = -cos(cameraAngle);
		break;

	case GLUT_KEY_RIGHT:
		//xCamera += 0.1;
		cameraAngle += 0.01f;
		lxCamera = sin(cameraAngle);
		lzCamera = -cos(cameraAngle);
		break;

	case GLUT_KEY_UP:
		//zCamera -= 0.1;
		xCamera += lxCamera * fraction;
		zCamera += lzCamera * fraction;
		break;

	case GLUT_KEY_DOWN:
		//zCamera += 0.1;
		xCamera -= lxCamera * fraction;
		zCamera -= lzCamera * fraction;
		break;
	}


	glutPostRedisplay();
}


void myMenu(int value) {
	if (value == 1)
	{
		exit(0);
	}
}

void projectionMenu(int value) {
	if (value == 1) {
		perspective = true;
	}
	if (value == 2) {
		perspective = false;
	}
}

void rotateMenu(int value) {
	if (value == 1)
	{
		Xrotation = 0;
		Yrotation = 0;
		Zrotation = 0;
	}
}

void colorMenu(int value) {
	if (value == 1) {
		Color = "red";
	}
	if (value == 2) {
		Color = "yellow";
	}
	if (value == 3) {
		Color = "blue";
	}
	if (value == 4) {
		Color = "green";
	}
}

void modelMenu(int value) {
	if (value == 1) {
		model = 1;
	}
	if (value == 2) {
		model = 2;
	}
	if (value == 3) {
		model = 3;
	}
}

void rotateX(int value) {
	switch (value)
	{
	case 1:
		Xrotation += 30;
		break;
	case 2:
		Xrotation += 60;
		break;
	case 3:
		Xrotation += 90;
		break;
	case 4:
		Xrotation += 120;
		break;
	case 5:
		Xrotation += 180;
		break;
	}
}

void rotateY(int value) {
	switch (value)
	{
	case 1:
		Yrotation += 30;
		break;
	case 2:
		Yrotation += 60;
		break;
	case 3:
		Yrotation += 90;
		break;
	case 4:
		Yrotation += 120;
		break;
	case 5:
		Yrotation += 180;
		break;
	}
}

void rotateZ(int value) {
	switch (value)
	{
	case 1:
		Zrotation += 30;
		break;
	case 2:
		Zrotation += 60;
		break;
	case 3:
		Zrotation += 90;
		break;
	case 4:
		Zrotation += 120;
		break;
	case 5:
		Zrotation += 180;
		break;
	}
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (perspective == true)
		gluPerspective(50.0, 1.0, 0, 7.0);
		//glFrustum(-1.7, 1.7, -1.7, 1.7, -100, 100); //Using this clips everything beyond a distance of 1? Unknown why...
	else
		glOrtho(-7, 7, -7, 7, -100, 100);

	/*
	gluLookAt(xCamera, 0, zCamera,		// Camera is located (x, y, z)
		xCamera, 0, zCamera-4.5,			// Camera is looking at (0, 0, 0)
		0.0f, 1.0f, 0.0f);	// Up vector is (0, 1, 0) (positive Y)
		*/
	gluLookAt(xCamera, 0, zCamera,		// Camera is located (x, y, z)
		xCamera + lxCamera, 0, zCamera + lzCamera,			// Camera is looking at (0, 0, 0)
		0.0f, 1.0f, 0.0f);	// Up vector is (0, 1, 0) (positive Y)
	
	// Draw the ground (a plane)
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, -1.0f, -100.f);
	glVertex3f(-100.0f, -1.0f, 100.f);
	glVertex3f(100.0f, -1.0f, 100.f);
	glVertex3f(100.0f, -1.0f, -100.f);
	glEnd();
	setColor();

	if (displayModel == true) {
		switch (model) {
		case 1:
			if (solid == true) {
				for (int i = -2; i < 2; i++)
					for (int j = -2; j < 2; j++)
					{
						glPushMatrix();
						glTranslatef(i * 10.0, 0, j * 10.0);
						drawRobot(1);
						glPopMatrix();
					}
			}
			else {
				for (int i = -2; i < 2; i++)
					for (int j = -2; j < 2; j++)
					{
						glPushMatrix();
						glTranslatef(i * 10.0, 0, j * 10.0);
						drawRobot(2);
						glPopMatrix();
					}
			}
			break;
		case 2:
			if (solid == true) {
				for (int i = -2; i < 2; i++)
					for (int j = -2; j < 2; j++)
					{
						glPushMatrix();
						glTranslatef(i * 10.0, 0, j * 10.0);
						drawCreeper(1);
						glPopMatrix();
					}
			}
			else {
				for (int i = -2; i < 2; i++)
					for (int j = -2; j < 2; j++)
					{
						glPushMatrix();
						glTranslatef(i * 10.0, 0, j * 10.0);
						drawCreeper(2);
						glPopMatrix();
					}
			}
			break;
		case 3:
			if (solid == true) {
				for (int i = -2; i < 2; i++)
					for (int j = -2; j < 2; j++)
					{
						glPushMatrix();
						glTranslatef(i * 10.0, 0, j * 10.0);
						drawPig(1);
						glPopMatrix();
					}
			}
			else {
				for (int i = -2; i < 2; i++)
					for (int j = -2; j < 2; j++)
					{
						glPushMatrix();
						glTranslatef(i * 10.0, 0, j * 10.0);
						drawPig(2);
						glPopMatrix();
					}
			}
			break;
		}
	}
	else {
		glPushMatrix();
		glColor3ub(0, 0, 0);
		glutSolidCube(0.5);
		glPopMatrix();
		glutPostRedisplay();
	}
	if (displayAxis == true) {
		drawAxes();
	}
	glutPostRedisplay();


	if (clearScreen == true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char** argv) {

	printf("\n\
----------------------------------------------------------------------------\n\
Robot Controls:\n\
- '1': view wireframe \t '2': view solid \t '3': toggle axes\n\
- '4': bend elbow \t 'F4': extend elbow\n\
- '5': raise shoulder \t 'F5': lower shoulder \n\
- '6': move leg backward 'F6': move leg forward \n\
- '7': bend knee \t 'F7': extend knee\n\
- '8': left leg backward 'F8' left left forward\n\
- '9': right leg backward 'F9' right leg forward\n\
Movement:\n\
- 'Up Key': walk forward 'Down Key': walk backward\n\
- 'Left key: walk left \t'Right key': walk right\n\
Extra:\n\
- 'Right click': Change model to creeper?! With movable legs?!\n\
- ESC to quit \n\
----------------------------------------------------------------------------\n");
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB); // RGB mode
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("Isaac Fowler (811046122)");

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glutDisplayFunc(MyDisplay); // call the drawing function
	glutKeyboardFunc(procKeys);
	glutSpecialFunc(specialKeys);
	//glutMouseFunc(mouseClick);

	//Menus
	//Future reference: make this a separate void function.
	int rotateXSubMenu = glutCreateMenu(rotateX);
	glutAddMenuEntry("30", 1);
	glutAddMenuEntry("60", 2);
	glutAddMenuEntry("90", 3);
	glutAddMenuEntry("120", 4);
	glutAddMenuEntry("180", 5);
	int rotateYSubMenu = glutCreateMenu(rotateY);
	glutAddMenuEntry("30", 1);
	glutAddMenuEntry("60", 2);
	glutAddMenuEntry("90", 3);
	glutAddMenuEntry("120", 4);
	glutAddMenuEntry("180", 5);
	int rotateZSubMenu = glutCreateMenu(rotateZ);
	glutAddMenuEntry("30", 1);
	glutAddMenuEntry("60", 2);
	glutAddMenuEntry("90", 3);
	glutAddMenuEntry("120", 4);
	glutAddMenuEntry("180", 5);
	int rotateSubMenu = glutCreateMenu(rotateMenu);
	glutAddSubMenu("X axis", rotateXSubMenu);
	glutAddSubMenu("Y axis", rotateYSubMenu);
	glutAddSubMenu("Z axis", rotateZSubMenu);
	glutAddMenuEntry("Reset", 1);
	//int projectionSubMenu = glutCreateMenu(projectionMenu);
	//glutAddMenuEntry("Perspective", 1);
	//glutAddMenuEntry("Orthographic", 2);
	int colorSubMenu = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Yellow", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Green", 4);
	int modelSubMenu = glutCreateMenu(modelMenu);
	glutAddMenuEntry("Robot", 1);
	glutAddMenuEntry("Creeper", 2);
	glutAddMenuEntry("Pig!", 3);

	glutCreateMenu(myMenu);
	glutAddSubMenu("Rotate", rotateSubMenu);
	//glutAddSubMenu("Projection", projectionSubMenu);
	glutAddSubMenu("Color", colorSubMenu);
	glutAddSubMenu("Model", modelSubMenu);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}