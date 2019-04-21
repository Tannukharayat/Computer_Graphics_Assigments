#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

int width = 700 , height = 500 ;
int i ,j;

vector<pair <int , int > > p , temp;
int x[2] , y[2];


class Clip{
public:	
	void drawClipingArea();
	void clip();
	void drawpoly();
}c;

void Clip :: drawpoly(){
	glColor3f(1.0,0,0);
	glBegin(GL_LINE_LOOP);
	for(int i = 0 ; i < p.size() - 1 ; i++){
		glVertex2i(p[i].first , p[i].second );
	}
	glEnd();
	glFlush();
}

void Clip :: drawClipingArea(){
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x[0] , y[0]);
	glVertex2i(x[1] , y[0]);
	glVertex2i(x[1] , y[1]);
	glVertex2i(x[0] , y[1]);
	glEnd();
	glFlush();
}


void check(pair<int,int> v1 , pair<int,int> v2 , int f ){
	int x1 = v1.first;
	int y1 = v1.second;
	int x2 = v2.first;
	int y2 = v2.second;
	int p,q;
	switch(f){
		case 1: // LEFT CLIP
				if(x1 <= x[0] && x2 >= x[0]){
					p = x[0];
					q =  ((float)(y2 - y1) / (x2 - x1))*(x[0] - x1) + y1;
					temp.push_back({p,q});
					temp.push_back(v2);	
				}
				
				else if(x1 >= x[0] && x2 <= x[0]){
					p = x[0];
					q = ((float) (y2 - y1)/(x2 - x1))*(x[0] - x1) + y1;
					temp.push_back({p,q});
				}
				else if(x1 >= x[0] && x2 >= x[0]){
					temp.push_back(v2);
				}
	   break;
		 
	  case 2: // right Clip
		 		if(x1 >= x[1] && x2 <= x[1]){
		 			p = x[1];
		 			q = ((float) (y2 - y1)/(x2 - x1))*(x[1] - x1) + y1;
		 			temp.push_back({p,q});
		 			temp.push_back(v2);
		 		}
		 		else if(x1 <= x[1] && x2 >= x[1] ){
		 			p = x[1];
		 			q = ((float) (y2 - y1)/(x2 - x1))*(x[1] - x1) + y1;
		 			temp.push_back({p,q});
		 			}
		 		 else if (x1 <= x[1] && x2 <= x[1])
		 			  temp.push_back(v2);	
	
				break;
		 case 3 : // top clip
		 		if(y1 >= y[0] && y2 <= y[0]){
		 			q = y[0];
		 			p = ((float)(x2 - x1)/(y2 - y1))*(y[0] - y1) + x1;
		 			temp.push_back({p ,q});
		 			temp.push_back(v2); 
		 		}
		 		else if(y1 <= y[0] && y2 >= y[0]){
		 			q = y[0];
		 			p = ((float)(x2 - x1)/(y2 - y1))*(y[0] - y1) + x1;
		 			temp.push_back({p ,q});
		 		  }
		 		else if(y1 <= y[0] && y2 <= y[0]) 	temp.push_back(v2);			
			
		break;
	
		case 4:
					if(y1 <= y[1] && y2 >= y[1]){
						q = y[1];
					    p = ((float)(x2 - x1)/(y2 - y1))*(y[1] - y1) + x1;
						temp.push_back({p ,q});
				 		temp.push_back(v2); }
				 	else if(y1 >= y[1] && y2 <= y[1] ){
			 		   q = y[1];
					   p = p = ((float)(x2 - x1)/(y2 - y1))*(y[1] - y1) + x1;
					   temp.push_back({p ,q});
			 		}
			 	 else if(y1 >= y[1] && y2 >= y[1])temp.push_back(v2);  	
		 			
		break;	
			  }	     	
   }

void Clip :: clip(){
	for(int f = 1 ; f < 5 ;f++){
		
		for(int i = 0 ; i < p.size() - 1 ; i++){
				check(p[i] , p[i+1] , f);
		}
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
		glClearColor(0.8,0,0,0);
		glBegin(GL_LINE_LOOP);
		for(int i = 0 ; i < temp.size() ; i++){
			glVertex2i(temp[i].first ,temp[i].second );
		} 
		glEnd();
		drawClipingArea();
		glFlush();
		p.clear();
		for(int i = 0 ; i < temp.size() ; i++){
			 p.push_back({temp[i].first,temp[i].second});
		}
		 p.push_back({temp[0].first,temp[0].second});
		temp.clear();
		
	}
}




void mouse(int button , int state , int a ,int b){
	b = 500 - b;
	if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN && i!=2){
		x[i] = a;
		y[i++] = b;
		if(i==2) c.drawClipingArea();
	}
	else if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN && j!=-1){
			j++;
			p.push_back({a , b });		
	}
	if(button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		if((float)j/2 > 1){	
			j=-1;
			p.push_back({p[0].first , p[0].second });
			c.drawpoly();	
		}	
	}
}

void init(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,700,0,500);
	glFlush();
}

void foo(unsigned char key , int x , int y ){
		if(key=='c'){
				glClearColor(0,0,0,0);
				glClear(GL_COLOR_BUFFER_BIT);
				glFlush();
				i = j =  0;
				p.clear(); 
		}
		if(key=='s') c.clip();

}

int main(int argc , char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(700,500);
	glutCreateWindow("POLYGON CLIPPING");
	init();
	glutKeyboardFunc(foo);
	glutMouseFunc(mouse);
	glutMainLoop();
}
