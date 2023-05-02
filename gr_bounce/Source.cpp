#include <glut.h>
#include<CameraUIControl.h>

#include<stdio.h>
#include<iostream>
#include<math.h>
#include "texture.h"
#include "iostream"

using namespace std;
int z = 0, dir = 0;
float rect_up = 3, rect_bottom = -292, per_rect_up = 2, per_rect_bottom = -293, cir_x = 0, cir_y = 0;

void pcircle(float r, int xc, int yc, int start, int end){
	float x, y;
	for (float teta = start; teta <= end; teta = teta + 0.5){
		x = r*cos(teta*3.14 / 180);
		y = r*sin(teta*3.14 / 180);
		glBegin(GL_LINES);
		glVertex2f(xc, yc);
		glVertex2f(xc + x, yc + y);
		glEnd();
		glFlush();
	}
}

void display()
{
	
	unsigned char col[3];
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluOrtho2D(-500, 500, -300, 300);
	//glFrustum(-5, 5, -5, 5, 0, 15);
	//gluPerspective(53, 1, 0, 3);
	//gluLookAt(0, 0, 2,
	//		  0, 0, 0,
	//		  0, 1, 0);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(-495, 295);
	glVertex2f(495, 295);
	glVertex2f(495, 295);
	glVertex2f(495, -295);
	glVertex2f(495, -295);
	glVertex2f(-495, -295);
	glVertex2f(-495, -295);
	glVertex2f(-495, 150);
	glVertex2f(-495, 250);
	glVertex2f(-495, 292);
	glVertex2f(-495, 0);
	glVertex2f(-20, 0);
	glVertex2f(60, 0);
	glVertex2f(310, 0);
	glVertex2f(250, -200);
	glVertex2f(340, -200);
	glVertex2f(410, -100);
	glVertex2f(492, -100);
	glEnd();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(cir_x, cir_y, 0);
	pcircle(30, -450, -262, 0, 360);
	glPopMatrix();
	glReadPixels(50, 7, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
	for (int i = 0; i < 3; i++)
		cout << int(col[i]) << endl;

	glColor3f(0.8039, 0.5215, 0);
	
	glRectf(-290, -292, -200, -180);

	glRectf(-20, rect_bottom, 60,rect_up);

	glRectf(-200, 0, -300, 50);
	glRectf(-300, 0, -400, 100);
	glRectf(-400, 0, -492, 150);

	glColor3f(0, 0, 0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-300, 50);
	glVertex2f(-300, 0);
	glVertex2f(-400, 100);
	glVertex2f(-400, 0);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(-500, 500, -300, 300);
	glViewport(0, 0, w, h);
}

void timer(int n)
{
	if (rect_bottom == -292 && rect_up == 3)
	{
		rect_bottom++;
		rect_up++;
		per_rect_bottom = -292;
		per_rect_up = 3;
	}
	else if (rect_bottom == -3 && rect_up == 292)
	{
		rect_bottom--;
		rect_up--;
		per_rect_bottom = -3;
		per_rect_up = 292;
	}
	else
	{
		if (rect_bottom > per_rect_bottom && rect_up > per_rect_up)
		{
			rect_bottom++;
			rect_up++;
			per_rect_bottom++;
			per_rect_up++;
		}
		if (rect_bottom < per_rect_bottom &&rect_up < per_rect_up)
		{
			rect_bottom--;
			rect_up--;
			per_rect_bottom--;
			per_rect_up--;
		}
	}
	if (z == 1)
	{
		unsigned char col[3];
		glReadPixels(50 + cir_x, 68 + cir_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
		if (int(col[0]) == 0 && int(col[1]) == 0 && int(col[2]) == 0 &&  dir<120)
		{
			dir++;
			cir_y ++;
		}
		else
		{
			z = 0;
			cir_y --;
		}
	}
	if (z == 0)
	{
		unsigned char col[3];
		glReadPixels(50 + cir_x, 7 + cir_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
		if (int(col[0]) == 0 && int(col[1]) == 0 && int(col[2]) == 0)
		{
			cir_y--;
		}
	}
	glutTimerFunc(1, timer, 1);
	glutPostRedisplay();
	
}

void keyboardright(int c, int x, int y)
{
	unsigned char col[3];
	if (c==GLUT_KEY_RIGHT)
	{
		glReadPixels(80 + cir_x, 38 + cir_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
		if (int(col[0]) == 0 && int(col[1]) == 0 && int(col[2]) == 0)
		{
			cir_x++;
		}
	}
	if (c == GLUT_KEY_LEFT)
	{
		glReadPixels(19 + cir_x, 38 + cir_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
		
		if (int(col[0]) == 0 && int(col[1]) == 0 && int(col[2]) == 0)
		{
			cir_x--;
		}
	}
	glutPostRedisplay();
}
void keyboardup(unsigned char c, int x, int y)
{
	unsigned char col[3];
	if (c == 'w')
	{
		dir = 0;
		z = 1;
		//glReadPixels(50 + cir_x, 68 + cir_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
		//if (int(col[0]) == 0 && int(col[1]) == 0 && int(col[2]) == 0)
		//{
			//cir_y += 3;
		//}

	}
	
	glutPostRedisplay();

}

void idle()
{
	unsigned char col[3];
	glReadPixels(50 + cir_x, 7 + cir_y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &col);
	if (int(col[0]) == 0 && int(col[1]) == 0 && int(col[2]) == 0)
	{
		cir_y -= 3;
	}
}


int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Bounce");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardup);
	glutSpecialFunc(keyboardright);
	
	glutTimerFunc(1, timer, 1);
	//glutIdleFunc(idle);
	//glutMouseFunc(mouse);
	//glutMotionFunc(mouse2);
	glutMainLoop();
	return(0);
}