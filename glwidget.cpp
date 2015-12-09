#include "glwidget.h"
#include<QGLWidget>
#include<C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\glm.hpp>
#include <C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\gtc\matrix_transform.hpp>
#include <gl/GL.h>
#include<glut.h>
#include<QtOpenGL>
#include<GL/glu.h>
#include<QTimer>
#include<glteach.h>

GLWidget::GLWidget(QWidget*parent):
    QGLWidget(parent)
{


    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer->start(16);

}
void GLWidget::initializeGL(){
    glEnable(GL_DEPTH_TEST);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ambLC.x =0.2;
    ambLC.y =0.2;
    ambLC.z =0.2;
    diffLC.x =0.8;
    diffLC.y =0.8;
    diffLC.z =0.8;
    specLC.x =1.0;
    specLC.y =1.0;
    specLC.z =1.0;
    shinLC.x= 1;
    shinLC.y= 1;
    shinLC.z= 1;
    Lpos0.x = 0;
    Lpos0.y = 1;
    Lpos0.z = 5;
    Lpos1.x = -3;
    Lpos1.y = 4;
    Lpos1.z = -5;
    glEnable(GL_NORMALIZE);

}
void GLWidget::paintGL(){
    glClearColor(1,1,1,.7);

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    mv = lookAt(eyeinit,centerinit,upinit);
    mv= mv*scal;
    GLfloat amb[]={ambLC.x,ambLC.y,ambLC.z,1};
    GLfloat diff[] ={diffLC.x,diffLC.y,diffLC.z,1};
    GLfloat spec[] ={specLC.x,specLC.y,specLC.z,1.0};
    GLfloat L0pos[] ={Lpos0.x,Lpos0.y,Lpos0.z,1};
    GLfloat shin[] ={shinLC.x,shinLC.y,shinLC.z,1};
    GLfloat L1pos[] = {Lpos1.x,Lpos1.y,Lpos1.z,1};
    float pixels[] = {
        0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
    };


     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shin);

    glLightfv(GL_LIGHT0, GL_POSITION, L0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0,GL_SHININESS,shin);
    glLightfv(GL_LIGHT1, GL_POSITION, L1pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT1,GL_SHININESS,shin);


    glColor4f(r,g,b,a);

    glutSolidTeapot(1);


      glColor4f(1,1,1,.5);
    plane = lookAt(stationEye,stationCenter,stationUp);
    plane = translater(0,-.75,0)*tran*plane*scaler(100,0.1,100);




    glLoadMatrixf(&plane[0][0]);


    glutSolidCube(1);
    glLoadMatrixf(&mv[0][0]);
}
void GLWidget::resizeGL(int w, int h){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     mv = perspective(fovy,aspect,zNear,zFar);
    glLoadMatrixf(&mv[0][0]) ;
    glViewport( 0, 0, w,h );

}
glm::mat4 GLWidget::perspective(float fovy, float aspect, float zNear, float zFar) {
    float d = cos(glm::radians(fovy) / 2) / sin(glm::radians(fovy) / 2);
    float A = -(zFar + zNear) / (zFar - zNear);
    float B = -(2 * zFar*zNear) / (zFar - zNear);

     glm::mat4 pers(
    d/aspect, 0, 0, 0,
       0, d, 0, 0,
       0, 0, A, B,
       0, 0,-1, 0);
     pers = glm::transpose(pers);
     return pers;
    //return glm::perspective(fovy, aspect, zNear, zFar);

}
glm::mat4 GLWidget::lookAt(const glm::vec3 &eye, const glm::vec3 &center, const glm::vec3 &up) {
    glm::vec3 a = eye - center;

    glm::vec3 w = glm::normalize(a);
    glm::vec3 u = glm::normalize(glm::cross(up, w));
    glm::vec3 v = glm::normalize(glm::cross(w, u));

    glm::mat4 look(
        u.x, u.y, u.z, -glm::dot(u,eye),
        v.x, v.y, v.z, -glm::dot(u,eye),
        w.x, w.y, w.z, -glm::dot(w,eye),
        0, 0, 0, 1
        );

    look = glm::transpose(look);

    return look;
}
glm::mat4 GLWidget::translater(const float &tx, const float &ty, const float &tz) {
   glm::mat4 ret(
        1, 0, 0, tx,
        0, 1, 0, ty,
        0, 0, 1, tz,
        0, 0, 0, 1);
    ret = glm::transpose(ret);
    return ret;
}
glm::mat3 GLWidget::rotate(const float degrees, const glm::vec3& axis1) {
    glm::vec3 axis = glm::normalize(axis1);
    glm::mat3 R;
    glm::mat3 I(1.0f);
    glm::mat3 second(
        axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
        axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
        axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);
    glm::transpose(second);
    glm::mat3 third(
        0, -axis.z, axis.y,
        axis.z, 0, -axis.x,
        -axis.y, axis.x, 0);
    glm::transpose(third);
    R = cos(glm::radians(degrees))*I + (1 - cos(glm::radians(degrees)))*second + sin(glm::radians(degrees))*third;

    return R;
}
void GLWidget::left(float degrees) {

    eyeinit = eyeinit*rotate(degrees, upinit);
   //updateGL();

}

void GLWidget::up(float degrees) {
    glm::vec3 a = glm::normalize(eyeinit);
    //upinit = glm::normalize(upinit);
    glm::vec3 cross = glm::cross(a, upinit);

    eyeinit = eyeinit*rotate(degrees, cross);
    upinit = upinit*rotate(degrees, cross);

}
glm::mat4 GLWidget::scaler(const float &sx, const float &sy, const float &sz) {
    glm::mat4 ret(
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1);
    ret = glm::transpose(ret);

    return ret;
}
void GLWidget::scale(int size){

    scal = scaler(size*0.01,size*0.01,size*.01);



}
void GLWidget::translate(int unitx,int unity,int unitz)
{
    tran = translater(unitx*-0.1,unity*.1,unitz*.1);
}
void GLWidget::setfovy(float deg, int width, int height){fovy = deg; resizeGL(width,height);}
void GLWidget::setzFar(float dist,int w, int h){zFar= dist; resizeGL(w,h);}
void GLWidget::setzNear(float dist,int w, int h){zNear = dist; resizeGL(w,h);}
void GLWidget::setDegreeStep(float deg){Fivedegrees = deg;}//remove

void GLWidget::setEyeX(float v){eyeinit.x=v;  }
void GLWidget::setCenterX(float v){centerinit.x=v;   }
void GLWidget::setUpX(float v){upinit.x = v;   }

void GLWidget::setEyeY(float v){eyeinit.y=v; stationEye.y=v; }
void GLWidget::setCenterY(float v){centerinit.y=v; }
void GLWidget::setUpY(float v){upinit.y = v;  }

void GLWidget::setEyeZ(float v){eyeinit.z=v;  }
void GLWidget::setCenterZ(float v){centerinit.z=v;  }
void GLWidget::setUpZ(float v){upinit.z = v; }
float GLWidget::getEyeX(){return eyeinit.x;}
float GLWidget::getEyeY(){return eyeinit.y;}
float GLWidget::getEyeZ(){return eyeinit.z;}
float GLWidget::getCenterX(){return centerinit.x;}
float GLWidget::getCenterY(){return centerinit.y;}
float GLWidget::getCenterZ(){return centerinit.z;}
float GLWidget::getUpX(){return upinit.x;}
float GLWidget::getUpY(){return upinit.y;}
float GLWidget::getUpZ(){return upinit.z;}
void GLWidget::setMatColor(glm::vec4 mat,glm::vec4 aLC,glm::vec4 sLC,glm::vec4 dLC,glm::vec4 spLC,glm::vec4 L0,glm::vec4 L1)
{
    r = mat.x;
    g = mat.y;
    b= mat.z;
    a = mat.w;
    ambLC= aLC;
    shinLC=sLC;
    diffLC=dLC;
    specLC=spLC;
    Lpos0=L0;
    Lpos1=L1;

}
