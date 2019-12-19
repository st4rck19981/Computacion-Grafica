//g++ bezier.cpp -o main -lglut -lGLU -lGL
//./main

//con tecla + para incrementar puntos en la recta
//con tecla - para decrementar puntos en la recta

#include <GL/glut.h>
#include <stdlib.h>

int connection=1;
GLfloat controlPoints[6][3]={
	{-4.0,-4.0, 0.0},
	{-2.0, 4.0, 0.0},
	{-3.0,-3.0, 0.0},
	{ 4.0, 4.0, 0.0},
	{ 2.0,-4.0, 0.0},
	{ 3.0, 2.0, 0.0}
};

void init(){
	glClearColor(0.0,0.0,0.0,0.0);
	glMap1f(GL_MAP1_VERTEX_3,0.0,1.0,3,4,&controlPoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_STRIP);

	for (int i=0;i<=connection;i++)
		glEvalCoord1f((GLfloat)i / (GLfloat)connection);
	glEnd();

	glPointSize(5.0);
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POINTS);

	for (int i=0;i<6;i++)
		glVertex3fv(&controlPoints[i][0]);
	glEnd();
	glFlush();
}

void reshape(int w, int h){
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-5.0,5.0,-5.0*(GLfloat)h / (GLfloat)w,
		5.0*(GLfloat)h / (GLfloat)w,-5.0,5.0);
	else
		glOrtho(-5.0*(GLfloat)w / (GLfloat)h,
		5.0*(GLfloat)w / (GLfloat)h, -5.0,5.0,-5.0,5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
		case 27:
			exit(0);
			break;
		case '+':
			connection++;
			break;
		case '-':
			connection--;
			break;
	}
	if (connection<0) connection=0;
	glutPostRedisplay();
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}