#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

int window;
double centreX, centreY, radius = 50,prevX=0, prevY=0, error = 0;

void drawPoints(double x, double y){
    printf("Drawing X=%d, Y=%d\n",x,y);
    glColor3f(0,0,0);
    glBegin(GL_POINTS);
    glVertex2i(x+centreX,y+centreY);
    glVertex2i(y+centreX,x+centreY);
    glVertex2i(y+centreX,-x+centreY);
    glVertex2i(-x+centreX,y+centreY);
    glVertex2i(-x+centreX,-y+centreY);
    glVertex2i(-y+centreX,-x+centreY);
    glVertex2i(-y+centreX,x+centreY);
    glVertex2i(x+centreX,-y+centreY);
    glEnd();
    glFlush();
}


void drawParametricCircle()
{
  double i=0, x = 1, y = 0;
  while(x >= y){
    x = (radius*cos(i));
    y = (radius*sin(i));
    drawPoints(x,y);
    i = i+0.0001;
  }
}
void keyPressed(unsigned char key, int x, int y){
  if(key == 27)
  glutDestroyWindow(window);
  if(key == 13)
  {
    drawParametricCircle();
  }
}

void mouseEvents(int button, int state, int x, int y){
  if( GLUT_DOWN == state && GLUT_RIGHT_BUTTON == button )
  {
    x = x - 683;
    y = 384 -y;
    printf("X=%d, Y=%d\n", x, y);
    centreX = x;
    centreY = y;
  }
}

void grid(){
  glColor3f(0,0,1);
  glBegin(GL_LINES);
  glVertex2i(0,384);
  glVertex2i(0,-384);
  glEnd();
  glBegin(GL_LINES);
  glVertex2i(683,0);
  glVertex2i(-683,0);
  glEnd();
}

void display()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  grid();
  glFlush();
}


void Init()
{
  /* Set clear color to white */
  glClearColor(1.0,1.0,1.0,0);
  /* Set fill color to black */
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(-683, 683, -384, 384);
}
int main(int argc, char **argv)
{

  /* Initialise GLUT library */
  glutInit(&argc,argv);
  /* Set the initial display mode */
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  /* Set the initial window position and size */
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1366,768);
  /* Create the window with title "DDA_Line" */
  window = glutCreateWindow("Circle");
  /* Initialize drawing colors */
  Init();
  /* Call the displaying function */
  glutDisplayFunc(display);
  glutMouseFunc(mouseEvents);
  glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
  /* Keep displaying untill the program is closed */
  glutMainLoop();
}
