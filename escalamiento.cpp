//g++ circulo.cpp -o main -lglut -lGLU -lGL
//  ./main
#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
//#include <c:\\GLUT\include\GL\glut.h>

float M[4][3]={{0,0,1},{0,4,1},{4,4,1},{4,0,1}};  //POLIGONO CUADRADO
float T[3][3]={{1,0,0},{0,1,0},{0,0,1}};
float R[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};  //GUARDAR RESULTADOS


void Escalamiento()
{
    T[0][0]=3;  //TRASLACION EN X
    T[1][1]=3;  //TRASLACION EN Y
    for(int p=0;p<4;p++){  //punto
        for(int i=0;i<3;i++){  //matriz
            for(int j=0;j<3;j++){
                R[p][i]+=T[i][j]*M[p][j];
            }
        }
    }
}

void inicio()
{
    glMatrixMode(GL_PROJECTION);//sirve para el uso de la pantalla
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(-20,20,-20,20);
}

void pantalla()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Escalamiento();

    //Escalamiento
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<4; i++)
    {
        glVertex2f(R[i][0],R[i][1]);
    }
    glEnd();

    //NORMAL
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<4; i++)
    {
        glVertex2f(M[i][0],M[i][1]);
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

    glutCreateWindow("Circulo");
    inicio();
    glutDisplayFunc(pantalla);

    glutMainLoop();//se repite y no se cierra

    return EXIT_SUCCESS;
}
