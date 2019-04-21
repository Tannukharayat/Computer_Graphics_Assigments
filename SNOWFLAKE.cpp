#include<iostream>
#include<GL/glut.h>
#include<math.h>

using namespace std;

double prevX = 100;
double prevY = 400;
double len = 100;
int state = 0;
double deg;
bool done;
int i;

void kotch(double dir, int iter){
	if(iter == 0){
		dir = dir*(3.14/180);
		double nexX = prevX + cos(dir)*len;
		double nexY = prevY + sin(dir)*len;
		glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex2d(prevX, prevY);
		glVertex2d(nexX, nexY);
		glEnd();
		prevX = nexX;
		prevY = nexY;
		return;
	}
	--iter;
	kotch(dir, iter);
	dir += 60;
	kotch(dir, iter);
	dir -= 120;
	kotch(dir, iter);
	dir += 60;
	kotch(dir, iter);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	if(done){
		len = len/pow(3, i);
		kotch(deg, i);
		kotch(deg-120, i);
		kotch(deg+120, i);
	}
	glFlush();
}

void mouse(int but, int st, int x, int y){
	y = 600 - y;
	if(but == GLUT_RIGHT_BUTTON || st == GLUT_UP)
		return;
	if(!done){
		if(!state){
			++state;
			prevX = x;
			prevY = y;
		}
		else{
			len = sqrt(pow(prevY - y, 2) + pow(prevX - x, 2));
			deg = atan2(y - prevY, x - prevX);
			deg *= (180/3.14);
			++state;
			done = true;
		}
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]){
	cin>>i;
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("kotch");

	gluOrtho2D(0, 600, 0, 600);
	
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;
}
