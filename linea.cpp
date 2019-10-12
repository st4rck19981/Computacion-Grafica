//g++ circulo.cpp -o main -lglut -lGLU -lGL
//  ./main
#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <math.h>
//#include <c:\\GLUT\include\GL\glut.h>

float x_1=0.0,x_2=19.0,y_1=0.0,y_2=6.0;
float m=(y_1-y_2)/(x_1-x_2);

void inicio()
{
    glMatrixMode(GL_PROJECTION);//sirve para el uso de la pantalla
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(-20,20,-20,20);// plano cartesiano de -20 a 20 en x y
}

void pantalla()
{
    glClear(GL_COLOR_BUFFER_BIT);
	
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POINTS);

    for(float i=x_1; i<=x_2; i+=0.001)
    {
        glVertex2f(i,m*i);
    }
    glEnd();

    glFlush();
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);//inicializa las funciones de GLUT
    glutInitWindowSize(600,600);//ancho y largo de la pantalla
    glutInitWindowPosition(10,10);//Posicion de la ventana
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Linea");
    inicio();
    glutDisplayFunc(pantalla);

    glutMainLoop();//se repite y no se cierra

    return EXIT_SUCCESS;
}
