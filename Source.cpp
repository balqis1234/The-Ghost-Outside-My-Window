#include <Windows.h>
#include <stdlib.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h> 
#include <io.h>
#include <math.h>
#include <iostream>

#define SCREEN_HEIGHT 1400
#define SCREEN_WIDTH 1400
#define PI 3.1415926535897932384626433832795
#define FPS 30

int x = 30;
int y = 50;
int dx = 10;//velocity
int dy = 15;

int winWidth = SCREEN_WIDTH, winHeight = SCREEN_HEIGHT, counter = 0;
time_t t;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

float elapsedTime = 0, base_time = 0, fps = 0, frames;

void calcFPS() {
	elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	if ((elapsedTime - base_time) > 1000.0) {
		fps = frames * 1000.0 / (elapsedTime - base_time);
		printf("fps: %f", fps);
		base_time = elapsedTime;
		frames = 0;
	}
	frames++;
}

void r_idle() {}

void MyTimerFunc(int value);

/*======================
********INITIALIZE******
*======================*/
void circle(int x, int y, int r);
void rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void triangle(int x1, int y1, int x2, int y2, int x3, int y3);
void line(float a, float b, float c, float d);
void car();
void road();
void cloud();
void lightning();
void ghost2();
void ghost2_move();

/*======================
********SHAPES**********
*======================*/

void circle(int x, int y, int r) // r = radius
{
	//draw a circle
	float theta;
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 360; i++)
	{
		theta = i * PI / 180;
		glVertex2f(x + r * cos(theta), y + r * sin(theta)); //x-axis , y-axis, 196 = radius
	}
	glEnd();
}

void rectangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();
}

void line(float a, float b, float c, float d) 
{
	glBegin(GL_LINES);
	glVertex2f(a, b);
	glVertex2f(c, d);
	glEnd();
}

/*===========================
********BACKGROUND**********
*===========================*/
void car()
{
	//upper car body
	glColor3f(0.0, 0.0, 0.5); //blue
	rectangle(0, 280, 1120, 280, 1400, -140, -560, -140);
	//bottom car body
	rectangle(-840, -140, 1400, -140, 1400, -700, -840, -700);

	//front- window (window 1)
	glColor3f(0.51, 0.47, 0.47); //lightest grey
	triangle(-476, -140, -28, 196, -28, -140);
	rectangle(28, 196, 560, 196, 560, -140, 28, -140);
	rectangle(644, 196, 1120, 196, 1120, -140, 644, -140);

	//wheel
	glColor3f(0.0, 0.0, 0.0); //black
	circle(-420, -798, 196); //front wheel
	circle(1036, -798, 196); // back wheel
}

void road()
{
	//road
	glColor3f(0.2, 0.21, 0.2); //light grey
	rectangle(-1400, -980, 1400, -980, 1400, -1400, -1400, -1400);
}

void cloud()
{
	glColor3f(0.17, 0.19, 0.21); //grey
	rectangle(-1400, 1400, 1400, 1400, 1400, 1260, -1400, 1260);
	circle(-1316, 1316, 140);
	circle(-1120, 1260, 196);
	circle(-840, 1260, 140);
	circle(-560, 1260, 252);
	circle(-280, 1260, 112);
	circle(0, 1260, 196);
	circle(280, 1260, 112);
	circle(420, 1260, 84);
	circle(560, 1260, 196);
	circle(700, 1260, 84);
	circle(840, 1260, 112);
	circle(980, 1260, 112);
	circle(1120, 1260, 196);
	circle(1260, 1260, 140);
}

void lightning()
{
	glColor3f(0.88, 0.90, 0.93);
	rectangle(-644, 1260, -560, 1260, -840, 616, -980, 560);
	rectangle(-980, 560, -840, 616, -588, 616, -700, 560);
	triangle(-700, 560, -588, 616, -840, 0);
}


/*===========================
***********GHOST 2**********
*===========================*/

void ghost2()
{
	// hair 
	glColor3f(0.0, 0.0, 0.0); //black
	circle(-980, -420, 112);
	circle(-700, -420, 112);
	triangle(-1092, -420, -980, -532, -1092, -532);
	triangle(-588, -420, -588, -532, -700, -532);
	rectangle(-1092, -532, -980, -532, -980, -616, -1092, -616);
	rectangle(-700, -532, -588, -532, -588, -616, -700, -616);
	rectangle(-1092, -616, -980, -616, -924, -672, -1092, -672);
	rectangle(-700, -616, -588, -616, -588, -672, -756, -672);
	rectangle(-1092, -672, -924, -672, -924, -980, -1092, -980);
	rectangle(-756, -672, -588, -672, -588, -980, -756, -980);

	//face 
	glColor3f(0.8, 0.8, 0.8); //light grey
	rectangle(-980, -532, -700, -532, -700, -616, -980, -616);
	rectangle(-980, -616, -700, -616, -812, -700, -868, -700);

	//mouth 1
	glColor3f(1.0, 0.0, 0.0); //red
	circle(-840, -560, 112);
	//mouth 2
	glColor3f(0.8, 0.8, 0.8); //light grey
	triangle(-952, -532, -728, -532, -840, -616);
	// hair 1
	glColor3f(0.0, 0.0, 0.0); //black
	rectangle(-980, -308, -700, -308, -700, -532, -980, -532);

	//cloth 
	glColor3f(1.0, 0.0, 0.0); //red
	rectangle(-924, -672, -868, -700, -868, -896, -924, -868);
	rectangle(-868, -700, -812, -700, -812, -896, -868, -896);
	rectangle(-812, -700, -756, -672, -756, -868, -812, -896);
	rectangle(-1176, -700, -1092, -700, -1092, -812, -1176, -728);
	rectangle(-588, -700, -560, -700, -532, -756, -588, -812);

	//left leg 
	glColor3f(0.91, 0.90, 0.89); //darker light grey
	rectangle(-1316, -476, -1176, -560, -1260, -672, -1344, -644);
	rectangle(-1400, -560, -1316, -476, -1344, -644, -1400, -728);

	//right leg 
	glColor3f(0.91, 0.90, 0.89); //darker light grey
	rectangle(-504, -560, -392, -476, -392, -672, -448, -728);
	rectangle(-392, -476, -140, -1008, -224, -1092, -392, -672);
	rectangle(-140, -1008, -84, -1008, -84, -1092, -224, -1092);

	//left arm 
	glColor3f(0.8, 0.8, 0.8); //light grey
	rectangle(-1260, -560, -1092, -560, -1092, -700, -1176, -700);
	rectangle(-1260, -560, -1176, -700, -1288, -1176, -1372, -1092);
	rectangle(-1400, -1092, -1372, -1092, -1288, -1176, -1400, -1176);

	//right arm 
	glColor3f(0.8, 0.8, 0.8); //light grey
	rectangle(-588, -560, -448, -560, -560, -700, -588, -700);
	rectangle(-560, -700, -448, -560, -392, -1092, -476, -1176);
	rectangle(-392, -1092, -336, -1092, -336, -1176, -476, -1176);
}

/*===========================
**********MOVEMENTS *********
*===========================*/

void ghost2_move()
{
	// hair 
	glColor3f(0.0, 0.0, 0.0); //black
	rectangle(-280, 700, 280, 700, 280, 420, -280, 420);
	circle(-280, 560, 140);
	circle(280, 560, 140);
	triangle(-420, 560, -280, 420, -420, 420);
	triangle(280, 420, 420, 560, 420, 420);
	rectangle(-420, 420, -280, 420, -280, 140, -420, 140);
	rectangle(280, 420, 420, 420, 420, 140, 280, 140);
	rectangle(-420, 140, -280, 140, -140, 56, -420, 56);
	rectangle(280, 140, 420, 140, 420, 84, 168, 84);
	rectangle(-420, 56, -140, 56, -140, -560, -420, -560);
	rectangle(168, 84, 420, 84, 420, -560, 168, -560);

	//cloth 
	glColor3f(1.0, 0.0, 0.0); //red
	rectangle(-140, 56, -28, 0, -28, -420, -140, -364);
	rectangle(-28, 0, 28, 0, 28, -420, -28, -420);
	rectangle(28, 0, 168, 84, 168, -364, 28, -420);
	triangle(-700, -28, -420, -28, -420, -280);
	triangle(420, -28, 700, -28, 420, -280);

	//face 
	glColor3f(0.8, 0.8, 0.8); //light grey
	rectangle(-280, 420, 280, 420, 280, 140, -280, 140);
	rectangle(-280, 140, 280, 140, 28, 0, -28, 0);

	//eye
	glColor3f(0.0, 0.0, 0.0); //black
	circle(-140, 336, 56);
	circle(140, 336, 56);
	glColor3f(1.0, 0.0, 0.0); //red
	circle(-140, 336, 14);
	circle(140, 336, 14);
	

	//mouth 
	glColor3f(1.0, 0.0, 0.0); //red
	triangle(-224, 196, 224, 196, 0, 28);
	
	//left leg 
	glColor3f(0.91, 0.90, 0.89); //darker light grey
	rectangle(-924, 364, -616, 140, -700, -56, -980, 168);
	rectangle(-1400, 0, -924, 364, -980, 168, -1400, -252);
	//right leg 
	rectangle(560, 140, 784, 364, 868, 168, 700, -56);
	rectangle(784, 364, 1400, 56, 1400, -196, 868, 168);

	//left arm 
	glColor3f(0.8, 0.8, 0.8); //light grey
	rectangle(-840, 140, -420, 140, -420, -56, -700, -56);
	rectangle(-1232, -560, -840, 140, -700, -56, -1232, -728);
	rectangle(-1400, -560, -1232, -560, -1232, -728, -1400, -728);
	//right arm 
	rectangle(420, 140, 840, 140, 700, -56, 420, -56);
	rectangle(840, 140, 1260, -644, 1260, -812, 700, -56);
	rectangle(1260, -644, 1400, -644, 1400, -812, 1260, -812);
}

/*===========================
******DISPLAY FUNCTION*******
*===========================*/

void display1() //scene with the ghost in front of the car (before lightning)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.12, 0.13, 0.12, 1.0); //background color - black
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	road();
	car();
	cloud();
	ghost2();

	glutSwapBuffers();
}

void display2() //first lightning
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.12, 0.13, 0.12, 1.0); //background color - black
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	road();
	car();
	cloud();
	ghost2();
	glColor3f(0.88, 0.90, 0.93);
	rectangle(-644, 1260, -560, 1260, -840, 616, -980, 560);

	glutSwapBuffers();
}

void display3() //second lightning
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.12, 0.13, 0.12, 1.0); //background color - black
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	road();
	car();
	cloud();
	ghost2();
	glColor3f(0.88, 0.90, 0.93);
	rectangle(-644, 1260, -560, 1260, -840, 616, -980, 560);
	rectangle(-980, 560, -840, 616, -588, 616, -700, 560);

	glutSwapBuffers();
}

void display4() //third or full lightning
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.12, 0.13, 0.12, 1.0); //background color - black
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	road();
	car();
	cloud();
	ghost2();
	lightning();

	glutSwapBuffers();
}

void display5() //lightning strike -> blinding Lily's eye
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.9, 0.89, 0.88, 1.0); 
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	glColor3f(0.91, 0.96, 0.93);
	road();
	//car
	//upper car body
	glColor3f(0.85, 0.8, 0.9); 
	rectangle(0, 280, 1120, 280, 1400, -140, -560, -140);
	//bottom car body
	rectangle(-840, -140, 1400, -140, 1400, -700, -840, -700);
	//front- window (window 1)
	glColor3f(0.9, 0.89, 0.88); 
	triangle(-476, -140, -28, 196, -28, -140);
	rectangle(28, 196, 560, 196, 560, -140, 28, -140);
	rectangle(644, 196, 1120, 196, 1120, -140, 644, -140);
	//wheel
	circle(-420, -798, 196); //front wheel
	circle(1036, -798, 196); // back wheel

	glColor3f(0.85, 0.8, 0.9);
	cloud();
	lightning();

	glutSwapBuffers();
}

void display6() //after lightning
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.12, 0.13, 0.12, 1.0); //background color - black
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	road();
	car();
	cloud();

	glutSwapBuffers();
}

void display7() //ghost suddenly appeared right in front of Lily out of nowhere
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.12, 0.13, 0.12, 1.0); //background color - black
	glLoadIdentity();
	gluOrtho2D(-SCREEN_WIDTH, SCREEN_WIDTH, -SCREEN_HEIGHT, SCREEN_HEIGHT);

	//objects / background
	road();
	car();
	cloud();
	ghost2_move();

	glutSwapBuffers();
}

void idle() {
	DWORD start = GetTickCount64();
	while (GetTickCount64() - start < 1000 / FPS);
	x += dx;
	y += dy;
	if (x < 0 || x > SCREEN_WIDTH) dx *= -1;
	if (y < 0 || y > SCREEN_HEIGHT) dy *= -1;
	glutPostRedisplay();
}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	glPointSize(10.0);
	glPointSize(10.0);
	glLineWidth(10.0);
}



/*===========================
***********MAIN**************
*===========================*/

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Outside Window");
	glutDisplayFunc(display1);
	glutReshapeWindow(1200, 1000);
	//glutTimerFunc(2000, timer, 0);

	glutIdleFunc(idle);
	glutTimerFunc(1000, MyTimerFunc, 0);
	srand(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initGL();
	glutMainLoop();
}

void MyTimerFunc(int value)
{
	if (value == 0)
	{
		glutDisplayFunc(display1);
		glutIdleFunc(display1);
		glutTimerFunc(1000, MyTimerFunc, 1);
	}

	if (value == 1)
	{
		glutDisplayFunc(display2);
		glutIdleFunc(display2);
		glutTimerFunc(1000, MyTimerFunc, 2);
	}

	
	if (value == 2)
	{
		glutDisplayFunc(display3);
		glutIdleFunc(display3);
		glutTimerFunc(1000, MyTimerFunc, 3);
	}

	if (value == 3)
	{
		glutDisplayFunc(display4);
		glutIdleFunc(display4);
		glutTimerFunc(1000, MyTimerFunc, 4);
	}

	if (value == 4)
	{
		glutDisplayFunc(display5);
		glutIdleFunc(display5);
		glutTimerFunc(1000, MyTimerFunc, 5);
	}

	if (value == 5)
	{
		glutDisplayFunc(display6);
		glutIdleFunc(display6);
		glutTimerFunc(1000, MyTimerFunc, 6);
	}

	if (value == 6)
	{
		glutDisplayFunc(display7);
		glutIdleFunc(display7);
		glutTimerFunc(1000, MyTimerFunc, 7);
	}
	
}