//Isaac Fowler
//Interactive model viewing program with zooming, rotation, color selection, and projection changing.
#include <GL/glut.h>
#include <string>
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600

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
int model = 1;

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

	//glColor3ub(0, 0, 255);
	//Body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1.5, 1);
	if (arg == 1)
		glutSolidCube(1.0);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Right arm
	glPushMatrix();
	glTranslatef(1, 0.4, 0);
	glScalef(1, 0.35, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Left arm
	glPushMatrix();
	glTranslatef(-1, 0.4, 0);
	glScalef(1, 0.35, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Right leg
	glPushMatrix();
	glTranslatef(0.3, -1.24, 0);
	glScalef(0.35, 1, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Left leg
	glPushMatrix();
	glTranslatef(-0.3, -1.24, 0);
	glScalef(0.35, 1, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
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
}

static void drawCreeper(int arg) {

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
	glTranslatef(-0.25, -1.08, 0.5);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Front Right Leg
	glPushMatrix();
	glTranslatef(0.25, -1.08, 0.5);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Back Left Leg
	glPushMatrix();
	glTranslatef(-0.25, -1.08, -0.5);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Back Right Leg
	glPushMatrix();
	glTranslatef(0.25, -1.08, -0.5);
	glScalef(0.5, 0.66, 0.5);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Face
	if (BlackAndWhite)
		glColor3d(0, 0, 0);
	else
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

void procKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w': // Wireframe
		solid = false;
		break;

	case 's': // Solid
		solid = true;
		break;

	case 'c': // Clear screen
		clearScreen = !clearScreen;
		break;

	case 'm': // Toggle model view
		displayModel = !displayModel;
		break;

	case 'a': //Toggle axis view
		displayAxis = !displayAxis;
		break;

	case 27:
		exit(0);
		break;
	}
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
}

void rotateX(int value) {
	switch (value)
	{
	case 1:
		Xrotation = 30;
		break;
	case 2:
		Xrotation = 60;
		break;
	case 3:
		Xrotation = 90;
		break;
	case 4:
		Xrotation = 120;
		break;
	case 5:
		Xrotation = 180;
		break;
	}
}

void rotateY(int value) {
	switch (value)
	{
	case 1:
		Yrotation = 30;
		break;
	case 2:
		Yrotation = 60;
		break;
	case 3:
		Yrotation = 90;
		break;
	case 4:
		Yrotation = 120;
		break;
	case 5:
		Yrotation = 180;
		break;
	}
}

void rotateZ(int value) {
	switch (value)
	{
	case 1:
		Zrotation = 30;
		break;
	case 2:
		Zrotation = 60;
		break;
	case 3:
		Zrotation = 90;
		break;
	case 4:
		Zrotation = 120;
		break;
	case 5:
		Zrotation = 180;
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

	gluLookAt(0, 0, zCamera,		// Camera is located (x, y, z)
		0, 0, 0,			// Camera is looking at (0, 0, 0)
		0.0f, 1.0f, 0.0f);	// Up vector is (0, 1, 0) (positive Y)
	
	if (BlackAndWhite == true)
		Color = "white";
	setColor();

	glRotatef(Xrotation, 1.0, 0.0, 0.0);
	glRotatef(Yrotation, 0.0, 1.0, 0.0);
	glRotatef(Zrotation, 0.0, 0.0, 1.0);
	if (displayModel == true) {
		switch (model) {
		case 1:
			if (solid == true) {
				drawRobot(1);
			}
			else {
				drawRobot(2);
			}
			break;
		case 2:
			if (solid == true) {
				drawCreeper(1);
			}
			else {
				drawCreeper(2);
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
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB); // RGB mode
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("Isaac Fowler (811046122)");

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glutDisplayFunc(MyDisplay); // call the drawing function
	glutKeyboardFunc(procKeys);
	glutMouseFunc(mouseClick);

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
	int projectionSubMenu = glutCreateMenu(projectionMenu);
	glutAddMenuEntry("Perspective", 1);
	glutAddMenuEntry("Orthographic", 2);
	int colorSubMenu = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Yellow", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Green", 4);
	int modelSubMenu = glutCreateMenu(modelMenu);
	glutAddMenuEntry("Robot", 1);
	glutAddMenuEntry("Creeper!?", 2);

	glutCreateMenu(myMenu);
	glutAddSubMenu("Rotate", rotateSubMenu);
	glutAddSubMenu("Projection", projectionSubMenu);
	glutAddSubMenu("Color", colorSubMenu);
	glutAddSubMenu("Model", modelSubMenu);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}