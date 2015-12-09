#ifndef GLWIDGET_H
#define GLWIDGET_H
#include<GL/gl.h>
#include <QGLWidget>
#include<QTimer>
#include <C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\gtc\matrix_transform.hpp>
#include<C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\glm.hpp>
#include <gl/GL.h>
#include<glut.h>
#include<QtOpenGL>
#include<GL/glu.h>
#include<QTimer>
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent=0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    glm::mat4 lookAt(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

    glm::mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    glm::mat4 translater(const float &tx, const float &ty, const float &tz);
    glm::mat3 rotate(const float degrees, const glm::vec3& axis1);
    glm::mat4 scaler(const float &sx, const float &sy, const float &sz);
    float getEyeX();
    float getEyeY();
    float getEyeZ();
    float getCenterX();
    float getCenterY();
    float getCenterZ();
    float getUpX();
    float getUpY();
    float getUpZ();
    float r=.5,g=.5,b=.5,a =1.0;
    glm::vec4 ambLC, shinLC, diffLC, specLC, Lpos0,Lpos1;
    void setMatColor(glm::vec4 mat,glm::vec4 ambLC,glm::vec4 shinLC,glm::vec4 diffLC,glm::vec4 specLC,glm::vec4 Lpos0,glm::vec4 Lpos1 );

public slots:
    void up(float);
    void left(float);
    void translate(int,int,int);
    void scale(int);
    void setfovy(float,int w,int h);
    void setzNear(float,int w, int h);
    void setzFar(float,int w, int h);
    void setDegreeStep(float);
    void setEyeX(float);
    void setCenterX(float);
    void setUpX(float);
    void setEyeY(float);
    void setCenterY(float);
    void setUpY(float);
    void setEyeZ(float);
    void setCenterZ(float);
    void setUpZ(float);


private:

    glm::vec3 stationEye= glm::vec3(0,0,5);
    glm::vec3 stationUp= glm::vec3(0,1,0);
    glm::vec3 stationCenter= glm::vec3(0,0,0);
    glm::mat4 plane;
    glm::mat4 mv;
    glm::mat4 scal;
    glm::mat4 tran;
    glm::vec3 eyeinit = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 upinit = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 centerinit = glm::vec3(0.0f, 0.0f, 0.0f);
    int w = 640, h = 480 ;
    float fovy = 90.0;
    float aspect = w/(float)h;
    float zNear = 0.1;
    float zFar = 99.0;
    float Fivedegrees = 5.0;
    QTimer* timer;


};

#endif // GLWIDGET_H
