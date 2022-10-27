//Isaac Fowler
//Added animation with three different cycles to toggle through and camera rotation and zoom.
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <string>
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600
#define PI 3.141592

//Joints
static int leftShoulderAngle = 0, rightShoulderAngle = 0;
static int elbowAngle = 20;
static int leftHipAngle = 0, rightHipAngle;
static int kneeAngle = -20;

bool solid = true;
bool clearScreen = false;
bool displayModel = true;
bool displayAxis = true;
bool displayPath = true;
std::string Color = "blue";
std::string prevColor;

int model = 1;
GLint leftMouseButton, rightMouseButton;	// Status of the mouse buttons
int mouseX = 0, mouseY = 0;					// Last known X and Y of the mouse
float cameraTheta, cameraPhi, cameraRadius;	// Camera position in spherical coordinates
float x, y, z;								// Camera position in cartesian coordinates

// Animation Variables
bool playAnimation = true;
int aniSeconds = 0;
int aniState = 0;

float walkingDistance = 0;
float jumpDistance = 0;
GLfloat walkingRotation = 0;
std::string animationType = "line";

void setColor();

static void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10);
	glEnd();
}

static void drawRobot(int arg) {
	//drawRobot(1) is solid and (2) is wireframe

	//Body
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 1.5, 0.5);
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
	glTranslatef(0.66, 0.5, 0);
	glRotatef((GLfloat)rightShoulderAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.25, 0);
	glScalef(0.35, 0.75, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0, -0.5, 0);
	glRotatef((GLfloat)elbowAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.35, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Left arm
	//Upper
	glPushMatrix();
	glTranslatef(-0.66, 0.5, 0);
	glRotatef((GLfloat)leftShoulderAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.25, 0);
	glScalef(0.35, 0.75, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0, -0.5, 0);
	glRotatef((GLfloat)elbowAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.35, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Right leg
	//Upper
	glPushMatrix();
	glTranslatef(0.3, -0.85, 0);	
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.20, 0);
	glScalef(0.35, 0.75, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0, -0.5, 0);
	glRotatef((GLfloat)kneeAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.35, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();

	//Left leg
	//Upper
	glPushMatrix();
	glTranslatef(-0.3, -0.85, 0);
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.20, 0);
	glScalef(0.35, 0.75, 0.35);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	//Lower
	glTranslatef(0, -0.5, 0);
	glRotatef((GLfloat)kneeAngle, 1.0, 0.0, 0.0);
	glTranslatef(0, -0.35, 0);
	if (arg == 1)
		glutSolidCube(1.0f);
	else if (arg == 2)
		glutWireCube(1.0);
	glPopMatrix();
}

static void drawPig(int arg) {

	glRotatef(180, 0.0, 1.0, 0.0);

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

	glRotatef(180, 0.0, 1.0, 0.0);

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
	glRotatef((GLfloat)rightHipAngle, 1.0, 0.0, 0.0);
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
	glRotatef((GLfloat)leftHipAngle, 1.0, 0.0, 0.0);
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
	else if (Color == "pink") {
		glColor3d(1, 0.1, 1);
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

void resetJoints() {
	rightHipAngle = 0; leftHipAngle = 0;
	rightShoulderAngle = 0; leftShoulderAngle = 0;
	if (animationType == "jump")
		kneeAngle = 0;
	else
		kneeAngle = -20;
	aniSeconds = 0;
}

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

	case 'p': //change walking path
		if (animationType == "line") {
			animationType = "circle";
			resetJoints();
		}
		else if (animationType == "circle") {
			animationType = "jump";
			resetJoints();
			jumpDistance = 0;
		}
		else {
			animationType = "line";
			resetJoints();
		}
		break;

	case 'a': //toggle animation
		playAnimation = !playAnimation;
		break;

	case 'r': //move to initial animation position
		walkingRotation = 0;
		walkingDistance = 0;
		jumpDistance = 0;
		resetJoints();
		displayAxis = false;

	case '3': //Toggle axis view
		displayAxis = !displayAxis;
		break;

	case '4': //Bend elbow
		displayPath = !displayPath;
		break;

	case 27:
		exit(0);
		break;
	}
}

//Mouse movement functions:
void recomputeOrientation()
{
	x = cameraRadius * sinf(cameraTheta) * sinf(cameraPhi);
	z = cameraRadius * cosf(cameraTheta) * sinf(cameraPhi);
	y = cameraRadius * cosf(cameraPhi);
	glutPostRedisplay();
}
void mouseCallback(int button, int state, int thisX, int thisY)
{
	// Update the left and right mouse button states, if applicable
	if (button == GLUT_LEFT_BUTTON)
		leftMouseButton = state;
	else if (button == GLUT_RIGHT_BUTTON)
		rightMouseButton = state;
	// and update the last seen X and Y coordinates of the mouse
	mouseX = thisX;
	mouseY = thisY;
}
void mouseMotion(int x, int y)
{
	if (leftMouseButton == GLUT_DOWN)
	{
		cameraTheta += (mouseX - x) * 0.005;
		cameraPhi += (mouseY - y) * 0.005;
		// Make sure that phi stays within the range (0, PI)
		if (cameraPhi <= 0)
			cameraPhi = 0 + 0.001;
		if (cameraPhi >= PI)
			cameraPhi = PI - 0.001;
		recomputeOrientation(); // Update camera (x, y, z)
	}
	// Camera zoom in/out
	else if (rightMouseButton == GLUT_DOWN)
	{
		double totalChangeSq = (x - mouseX) + (y - mouseY);

		cameraRadius += totalChangeSq * 0.01;

		// Limit the camera radius to some reasonable values so the user can't get lost
		if (cameraRadius < 2.0)
			cameraRadius = 2.0;
		if (cameraRadius > 15.0)
			cameraRadius = 15.0;
		recomputeOrientation(); // Update camera (x, y, z) based on (radius, theta, phi)
	}
	mouseX = x;
	mouseY = y;
}

void myMenu(int value) {
	if (value == 1)
	{
		exit(0);
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
		Color = "pink";
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

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, 0, 7.0);

	gluLookAt(x, y, z,		// Camera is located (x, y, z)
		0, 0, 0,			// Camera is looking at (0, 0, 0)
		0.0f, 1.0f, 0.0f);	// Up vector is (0, 1, 0) (positive Y)

	// Draw the ground (a plane)
	glColor3f(0.2f, 1.0f, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, -1.0f, -100.f);
	glVertex3f(-100.0f, -1.0f, 100.f);
	glVertex3f(100.0f, -1.0f, 100.f);
	glVertex3f(100.0f, -1.0f, -100.f);
	glEnd();

	glColor3f(1, 1, 0);
	if (displayPath == true) {
		if (animationType == "line") {
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, -100);
			glEnd();
		}
		else if (animationType == "circle") {
			glBegin(GL_LINE_LOOP);
			for (double i = 0; i < 2 * PI; i += PI / 24)
				glVertex3f(cos(i) * 3, 0.0, sin(i) * 3);
			glEnd();
		}
		else {
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 3, 0);
			glEnd();
		}
	}

	setColor();

		switch (model) {
		case 1:
			if (solid == true) {
				glPushMatrix();
				if (animationType == "line")
					glTranslatef(0, 0, -walkingDistance);
				if (animationType == "circle") {
					glRotatef(walkingRotation, 0, 1, 0);
					glTranslatef(3, 0, 0);
				}
				if (animationType == "jump") {
					glTranslatef(0, jumpDistance, 0);
				}
				drawRobot(1);
				glPopMatrix();
			}
			else {
				glPushMatrix();
				if (animationType == "line")
					glTranslatef(0, 0, -walkingDistance);
				if (animationType == "circle") {
					glRotatef(walkingRotation, 0, 1, 0);
					glTranslatef(3, 0, 0);
				}
				if (animationType == "jump") {
					glTranslatef(0, jumpDistance, 0);
				}
				drawRobot(2);
				glPopMatrix();
			}
			break;
		case 2:
			if (solid == true) {
				glPushMatrix();
				if (animationType == "line")
					glTranslatef(0, 0, -walkingDistance);
				if (animationType == "circle") {
					glRotatef(walkingRotation, 0, 1, 0);
					glTranslatef(3, 0, 0);
				}
				if (animationType == "jump") {
					glTranslatef(0, jumpDistance, 0);
				}
				drawCreeper(1);
				glPopMatrix();
			}
			else {
				glPushMatrix();
				if (animationType == "line")
					glTranslatef(0, 0, -walkingDistance);
				if (animationType == "circle") {
					glRotatef(walkingRotation, 0, 1, 0);
					glTranslatef(3, 0, 0);
				}
				if (animationType == "jump") {
					glTranslatef(0, jumpDistance, 0);
				}
				drawCreeper(2);
				glPopMatrix();
			}
			break;
		case 3:
			if (solid == true) {
				glPushMatrix();
				if (animationType == "line")
					glTranslatef(0, 0, -walkingDistance);
				if (animationType == "circle") {
					glRotatef(walkingRotation, 0, 1, 0);
					glTranslatef(3, 0, 0);
				}
				if (animationType == "jump") {
					glTranslatef(0, jumpDistance, 0);
				}
				drawPig(1);
				glPopMatrix();
			}
			else {
				glPushMatrix();
				if (animationType == "line")
					glTranslatef(0, 0, -walkingDistance);
				if (animationType == "circle") {
					glRotatef(walkingRotation, 0, 1, 0);
					glTranslatef(3, 0, 0);
				}
				if (animationType == "jump") {
					glTranslatef(0, jumpDistance, 0);
				}
				drawPig(2);
				glPopMatrix();
			}
			break;
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

void timer(int v)
{
	if (displayModel)
	{
		if (playAnimation)
		{
			if (animationType == "line") {
				walkingDistance += 0.0175;
			}
			if (animationType == "circle") {
				walkingRotation += 0.5;
			}
			if (animationType == "jump") {
				if (aniSeconds < 30) {
					kneeAngle -= 2;
					leftHipAngle += 1;
					rightHipAngle += 1;
					rightShoulderAngle -= 1;
					leftShoulderAngle -= 1;
					jumpDistance -= 0.02;
				}
				else if (aniSeconds < 45) {
					jumpDistance += 0.15;
					if (leftHipAngle > 0) {
						leftHipAngle -= 4;
						rightHipAngle -= 4;
					}
					if (kneeAngle < 0)
						kneeAngle += 4;
					rightShoulderAngle += 10;
					leftShoulderAngle += 10;
				}
				else if (aniSeconds < 60) {
					jumpDistance += 0.07;
				}
				else if (aniSeconds < 75) {
					jumpDistance += 0.04;
				}
				else if (aniSeconds < 90) {
					jumpDistance -= 0.04;
					rightShoulderAngle -= 5;
					leftShoulderAngle -= 5;
				}
				else if (aniSeconds < 120) {
					jumpDistance -= 0.09;
					if (leftShoulderAngle > 0) {
						rightShoulderAngle -= 5;
						leftShoulderAngle -= 5;
					}
				}
				else if (aniSeconds < 135) {
					kneeAngle -= 4;
					leftHipAngle += 2;
					rightHipAngle += 2;
					jumpDistance -= 0.04;
				}
				else if (aniSeconds < 150) {
					kneeAngle += 4;
					leftHipAngle -= 2;
					rightHipAngle -= 2;
					jumpDistance += 0.04;
				}
				aniSeconds++;
				if (aniSeconds > 250)
					aniSeconds = 0;
			}
			else {
				if (aniSeconds <= 30 && aniState == 0)
				{
					rightShoulderAngle += 1;
					leftShoulderAngle -= 1;
					rightHipAngle += 1;
					leftHipAngle -= 1;
					aniSeconds++;
					if (aniSeconds >= 30)
						aniState = 1;
				}
				else
				{
					rightShoulderAngle -= 1;
					leftShoulderAngle += 1;
					rightHipAngle -= 1;
					leftHipAngle += 1;
					aniSeconds--;
					if (aniSeconds <= -30)
						aniState = 0;
				}
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, v);
}

int main(int argc, char** argv) {

	printf("\n\
----------------------------------------------------------------------------\n\
Controls:\n\
- '1': view wireframe \t '2': view solid\n\
- '3': toggle axes \t '4': toggle path\n\
- 'r': move to initial position\n\
- 'a': toggle walking animation\n\
- 'p': change walking path (line, circle, jump)\n\
Movement:\n\
- 'Left Mouse button': Rotate camera view\n\
- 'Right Mouse button': Zoom in and out\n\
- 'Middle Mouse button': Open menu\n\
Extra:\n\
- 'I added a pig and creeper that can walk\n\
and also a jumping animation!\n\
- ESC to quit \n\
----------------------------------------------------------------------------\n");
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB); // RGB mode
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("Isaac Fowler (811046122)");

	// Give the camera a 'pretty' starting point!
	cameraRadius = 10.0f;
	cameraTheta = 2.80;
	cameraPhi = 1.2; //2.0;
	recomputeOrientation();

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen

	//Callback functions:
	glutDisplayFunc(MyDisplay); // call the drawing function
	glutKeyboardFunc(procKeys);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(mouseMotion);
	glutTimerFunc(0, timer, 0);

	//Menus
	int colorSubMenu = glutCreateMenu(colorMenu);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Yellow", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Pink", 4);
	int modelSubMenu = glutCreateMenu(modelMenu);
	glutAddMenuEntry("Robot", 1);
	glutAddMenuEntry("Creeper", 2);
	glutAddMenuEntry("Pig!", 3);

	glutCreateMenu(myMenu);
	glutAddSubMenu("Color", colorSubMenu);
	glutAddSubMenu("Model", modelSubMenu);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutMainLoop();
	return 0;
}