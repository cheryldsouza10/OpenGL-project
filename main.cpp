#include <windows.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include<stdio.h>

void display();
void reshape(int,int);


const float clockR    = 4.0f,
            clockVol  = 4.0f,

            angle1min = M_PI / 30.0f,

            minStart  = 0.9f,
            minEnd    = 1.0f,

            stepStart = 0.8f,
            stepEnd   = 1.0f;

float angleHour = 0,
      angleMin  = 0,
      angleSec  = 0;



void newLine(float rStart, float rEnd, float angle){
  float c = cos(angle), s = sin(angle);
  glVertex2f( clockR*rStart*c, clockR*rStart*s);
  glVertex2f( clockR*rEnd*c, clockR*rEnd*s);
}



void RenderScene(void){
  int i;

glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);

  glBegin(GL_LINES);
    for(i=0; i<60; i++){
      if(i%5){ // normal minute
        if(i%5 == 1)
          glColor3f(1.0f, 1.0f, 1.0f);
        newLine(minStart, minEnd, i*angle1min);
      }else{
        glColor3f(1.0f, 0.0f, 0.0f);
        newLine(stepStart, stepEnd, i*angle1min);
      }
    }
  glEnd();

  glLineWidth(3.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.5f, -angleHour+M_PI/2);
    newLine(0.0f, 0.8f, -angleMin+M_PI/2);
  glEnd();

  glLineWidth(1.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.8f, -angleSec+M_PI/2);
  glEnd();

  glutSwapBuffers();
}



///////////////////////////////////////////////////////////
// Called by GLUT library when the window has chanaged size
int hourhand=5;

void presskey(unsigned char key,int x,int y)
{
    if(key=='a')
        hourhand=1;
    if(key=='b')
        hourhand=5;
    if(key=='c')
        hourhand=7;
}

void TimerFunction(int value){
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);


  angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(hourhand> 12 ? hourhand-12 : hourhand)/6.0f * M_PI+
              angleMin/12.0f;




  glutPostRedisplay();
  glutTimerFunc(33,TimerFunction, 1);
}




void output()
{

char strings[]="Class a at 1pm Class b at 5pm Class c at 7pm";
  glColor3f( 1.0,1.0,1.0);
  glRasterPos2f(1.0,1.0);
  int len, i;
  len = (int)strlen(strings);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, strings[i]);
  }

}

int zpos=-15.0;

void timer(int key,int x,int y)
{
        //glutTimerFunc(100000/60,timer,1.0);
        if(zpos>=-15.0 && key==GLUT_KEY_DOWN){
            zpos-=1.15;


        }


        else if(zpos<=-7.0 && key==GLUT_KEY_UP)
            zpos+=0.15;


        glutPostRedisplay();
}

void display()
{
 glClear(GL_COLOR_BUFFER_BIT);
 glLoadIdentity();

 glTranslatef(0,0.0,zpos);

 //middle
 glColor3f(0.729412,0.829412,0.529412);
 glBegin(GL_POLYGON);

     glVertex3f(-5.0,5.0,0.0);
     glVertex3f(5.0,5.0,0.0);
     glVertex3f(5.0,-5.0,0.0);
     glVertex3f(-5.0,-5.0,0.0);

 glEnd();

 //left
 glColor3f( 0.8,0.5,0.3);

 glBegin(GL_POLYGON);

     glVertex2f(-10.0,10.0);
     glVertex2f(-5.0,5.0);
     glVertex2f(-5.0,-5.0);
     glVertex2f(-10.0,-10.0);

 glEnd();

 //right
glBegin(GL_POLYGON);

     glVertex2f(10.0,10.0);
     glVertex2f(5.0,5.0);
     glVertex2f(5.0,-5.0);
     glVertex2f(10.0,-10.0);

 glEnd();

//bottom
 glColor3f( 0.59,0.5,0.3);
 glBegin(GL_POLYGON);

     glVertex2f(-5.0,-5.0);
     glVertex2f(5.0,-5.0);
     glVertex2f(10.0,-10.0);
     glVertex2f(-10.0,-10.0);

 glEnd();

 //top
 glBegin(GL_POLYGON);

     glVertex2f(-10.0,10.0);
     glVertex2f(10.0,10.0);
     glVertex2f(5.0,5.0);
     glVertex2f(-5.0,5.0);

 glEnd();

 //window
glColor3f( 0.629412,0.929412,0.729412);

 glBegin(GL_POLYGON);

     glVertex2f(-8.5,4.0);
     glVertex2f(-6.0,2.5);
     glVertex2f(-6.0,-2.5);
     glVertex2f(-8.5,-4.0);

 glEnd();

  //door
glColor3f( 0.3,0.3,0.3);

 glBegin(GL_POLYGON);

     glVertex2f(3.0,0.0);
     glVertex2f(4.5,0.0);
     glVertex2f(4.5,-5.0);
     glVertex2f(3.0,-5.0);

 glEnd();

   //black board
glColor3f( 0.0,0.0,0.0);

 glBegin(GL_POLYGON);

     glVertex2f(-2.5,2.5);
     glVertex2f(2.5,2.5);
     glVertex2f(2.5,-2.5);
     glVertex2f(-2.5,-2.5);

 glEnd();

 //podium
glColor3f( 0.64,0.16,0.16);

 glBegin(GL_POLYGON);

     glVertex2f(-4.0,-4.0);
     glVertex2f(2.8,-4.0);
     glVertex2f(2.8,-5.0);
     glVertex2f(-4.0,-5.0);

 glEnd();

 //teacher
 float theta;
 glTranslatef(-7.0,-2.0,zpos);
 glColor3f(1.0,1.0,1.0);
 glBegin(GL_POLYGON);
 for(int i=0;i<360;i++)
 {
     theta=i*3.142/180.0;
     glVertex2f(0.6*cos(theta),0.6*sin(theta));
 }
 glEnd();

 //original coordinates
 glTranslatef(0.0,0.0,zpos);


 //leg1
 glColor3f(1.0,1.0,1.0);
 glBegin(GL_POLYGON);

 glVertex2f(-4.5,-5.5);
 glVertex2f(-3.5,-5.5);
 glVertex2f(-4.0,-10.0);

 glEnd();

  //leg2
 glColor3f(1.0,1.0,1.0);
 glBegin(GL_POLYGON);

 glVertex2f(-3.5,-5.5);
 glVertex2f(-2.5,-5.5);
 glVertex2f(-3.0,-10.0);

 glEnd();

//body
if(hourhand==5)
glColor3f(1.0,0.0,0.0);
else if(hourhand==7)
glColor3f(0.0,1.0,0.0);
else if(hourhand==1)
glColor3f(0.0,0.0,1.0);
 glBegin(GL_POLYGON);

 glVertex2f(-3.5,-2.0);
 glVertex2f(-5.5,-6.5);
 glVertex2f(-1.5,-6.5);

 glEnd();

 //text
 output();

 //clock
 glTranslatef(18.0,13.0,-1.0);
 RenderScene();

 glFlush();

}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,2.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("Teacher in a class");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(timer);
    glutKeyboardFunc(presskey);
    glutTimerFunc(33, TimerFunction, 1);




    glutMainLoop();
}
