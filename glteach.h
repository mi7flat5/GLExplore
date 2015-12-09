#ifndef GLTEACH_H
#define GLTEACH_H
#include<C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\glm.hpp>
#include <QMainWindow>
#include<GL/glu.h>
#include<glwidget.h>

namespace Ui {
class GLTeach;
}

class GLTeach : public QMainWindow
{
    Q_OBJECT

public:
    explicit GLTeach(QWidget *parent = 0);
    ~GLTeach();

public slots:
    void infoUpdate();
    void rotateV();
    void rotateH();
    void animate();
    void updateFovy();
    void updatezNear();
    void updatezFar();
    void setDeg();

    void setEyeX();
    void setCenterX();
    void setUpX();
    void setEyeY();
    void setCenterY();
    void setUpY();
    void setEyeZ();
    void setCenterZ();
    void setUpZ();
    void callScale();
    void setMatColors();
    void moveXY();
private:
    Ui::GLTeach *ui;
    int intDegreeV;
    int intDegreeH;
    float deg = 5.0;
    int scale =1;
    glm::vec4 matColors;
    glm::vec4 ambLC, shinLC, diffLC, specLC, Lpos0,Lpos1;
    glm::vec3 translate;
    QTimer*timer;
    QTimer* timer2;
};

#endif // GLTEACH_H
