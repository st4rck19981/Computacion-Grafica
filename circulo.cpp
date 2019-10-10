//g++ cuadrado2d.cpp -o main -lglut -lGLU -lGL
//  ./main
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
//#include <c:\\GLUT\include\GL\glut.h>

float px=2,py=5,radio=3,calx,caly;

void inicio()
{
    glMatrixMode(GL_PROJECTION);//sirve para el uso de la pantalla
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(-20,20,-20,20);
}

void pantalla()
{
    glClear(GL_COLOR_BUFFER_BIT);
	
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    for(float i=0.0; i<10; i+=0.001)
    {
        calx = radio*cos(i);
        caly = radio*sin(i);
        glVertex2f(calx,caly);
    }
    glEnd();

    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);//inicializa las funciones de GLUT
    glutInitWindowSize(600,600);//ancho y largo de la pantalla
    glutInitWindowPosition(10,10);//Posicioin de la ventana
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Circulo");
    inicio();
    glutDisplayFunc(pantalla);

    glutMainLoop();//se repite y no se cierra

    return EXIT_SUCCESS;
}
