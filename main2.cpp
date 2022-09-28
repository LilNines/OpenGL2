//
//  Main2.cpp
//

#include <string>
#include <sstream> //convert numbers to text

#include "GetGlut.h"
#include "Sleep.h"
#include "ObjLibrary/SpriteFont.h"

using namespace std;
using namespace ObjLibrary;

void initDisplay();
void keyboard(unsigned char key, int x, int y);
void update();
void reshape(int w, int h);
void display();

// add global variabels here
SpriteFont font;
//represent the current window size
int window_width = 640;
int window_height = 480;

int main(int argc, char* argv[])
{
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0, 0);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutCreateWindow("Sprite Fonts");
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	initDisplay();
	// load your font here
	font.load("Font.bmp"); //If you call it before, it will fail to load the texture and generate an incomprehensible error message referring to assert.
	glutMainLoop();

	return 1;
}

void initDisplay()
{
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // on [ESC]
		exit(0); // normal exit
		break;
	}
}

void update()
{
	//update your variables here
	
	sleep(1.0 / 60.0);
	glutPostRedisplay();
}

//to resize the window
void reshape(int w, int h)
{
	glViewport (0, 0, w, h);

	// update window size variables here
	window_width = w;
	window_height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)w / (GLdouble)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void display()
{
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// clear the screen - any drawing before here will not display

	glLoadIdentity();
	gluLookAt(5.0, 3.0, 4.0,
	          0.0, 0.0, 0.0,
	          0.0, 1.0, 0.0);
	// set up the camera - any drawing before here will display incorrectly

	// display positive X, Y, and Z axes near origin
	glBegin(GL_LINES);
		glColor3d(1.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(2.0, 0.0, 0.0);
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 2.0, 0.0);
		glColor3d(0.0, 0.0, 1.0);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, 2.0);
	glEnd();

	glColor3d(0.6, 0.4, 0.2);
	glutSolidSphere(1.0, 20, 10);

	// add your text drawing code here (SpriteFont)
	//to set up a flat 2D coordinate system 640 by 480 units in size
	SpriteFont::setUp2dView(window_width, window_height);

	//convert part
	stringstream ss;
	ss << "Black" << 14; //same as cout //You don't need an endl. The result will be Black14.
	float x = 5.9f;
	ss << "(" << x << ")";
	string black_string = ss.str();

	//display the text "Hello World!" starting at (260, 220), which is about in the middle of the screen.
	font.draw("Hello World!", 250, 220, SpriteFont::BOLD);
	//display messages in different colours (the last three numbers are RGB values from 0 to 255)
	font.draw("Red Text", 385, 260, 255, 0, 0);
	font.draw("Yellow Text", 375, 180, 255, 255, 0);
	font.draw("Green Text", 275, 140, 0, 255, 0);
	font.draw("Cyan Text", 165, 180, 0, 255, 255);
	font.draw("Blue Text", 165, 260, 0, 0, 255);
	font.draw("Purple Text", 275, 300, 255, 0, 255, SpriteFont::ITALICS);
	//convert numbers to text part //The string can now be displayed
	font.draw(black_string, 50, 400, 0, 0, 0);

	// send the current image to the screen - any drawing after here will not display
	glutSwapBuffers();
	//After the drawing your text, restore the old view with the unsetUp2dView function in the SpriteFont class
	//If you do not call unsetUp2dView before calling setUp2dView next time the screen is displayed, your program will crash.
	SpriteFont::unsetUp2dView();
}
