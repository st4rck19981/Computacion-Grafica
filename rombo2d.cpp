//g++ cuadrado2d.cpp -o main -lglut -lGLU -lGL
//  ./main
#include <GL/glut.h>
 
void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glEnable(GL_COLOR_MATERIAL);
        glVertex3f(0.2,0,0);
        glColor3f(1.0,1.0,0);  //colores
        glVertex3f(0,0.2,0);
        glVertex3f(0.2,0.4,0);
        glVertex3f(0.4,0.2,0);
    glEnd();
    glFlush();
}
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}