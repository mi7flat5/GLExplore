#include "glteach.h"
#include "ui_glteach.h"
#include"glwidget.h"
#include<QtOpenGL>
#include<QTimer>
#include<iostream>
#include <C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\gtc\matrix_transform.hpp>
#include<C:\Users\Shane\Documents\GLTeach\glm-0.9.2.7\glm\glm.hpp>
GLTeach::GLTeach(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLTeach)
{
    ui->setupUi(this);
    intDegreeV =0;
    intDegreeH=0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(animate()));

    timer2 = new QTimer(this);
    connect(timer2,SIGNAL(timeout()),this,SLOT(infoUpdate()));
    timer2->start(300);


}

GLTeach::~GLTeach()
{
    delete ui;
}
void GLTeach::infoUpdate()
{
    ui->eyeXdisp->display(ui->widget->getEyeX());
    ui->eyeYdisp->display(ui->widget->getEyeY());
    ui->eyeZdisp->display(ui->widget->getEyeZ());
    ui->centerXdisp->display(ui->widget->getCenterX());
    ui->centerYdisp->display(ui->widget->getCenterY());
    ui->centerZdisp->display(ui->widget->getCenterZ());
    ui->upXdisp->display(ui->widget->getUpX());
    ui->upYdisp->display(ui->widget->getUpY());
    ui->upZdisp->display(ui->widget->getUpZ());
    this->setMatColors();
}
void GLTeach::rotateH()
{

    float rotdeg =5.0;
    if (intDegreeH<= ui->horizontalSlider->value())
        {ui->widget->left(rotdeg);}
    else if(intDegreeH> ui->horizontalSlider->value())
        {ui->widget->left(-rotdeg);}
    intDegreeH= ui->horizontalSlider->value();

}
void GLTeach::rotateV()
{
    float rotdeg=5.0;
    if (intDegreeV<= ui->verticalSlider->value())
        {ui->widget->up(rotdeg);}
    else if(intDegreeV> ui->verticalSlider->value())
        {ui->widget->up(-rotdeg);}
    intDegreeV= ui->verticalSlider->value();


}
void GLTeach::animate()
{

    if (ui->checkBox->isChecked())
    {
        timer->start(16);
        //ui->widget->up(deg);
        ui->widget->left(-deg);

     }
    else if (!ui->checkBox->isChecked())
    {timer->stop();}

}
void GLTeach::updateFovy()
{
    ui->widget->setfovy(ui->fovySpinBox->value(),ui->widget->width(),ui->widget->height());
}
void GLTeach::updatezNear()
{
    ui->widget->setzNear(ui->zNearSpinBox->value(),ui->widget->width(),ui->widget->height());
}
void GLTeach::updatezFar()
{
    ui->widget->setzFar(ui->zFarSpinBox->value(),ui->widget->width(),ui->widget->height());
}
void GLTeach::setDeg(){deg = ui->degSpinBox->value();}

void GLTeach::setEyeX(){ui->widget->setEyeX(ui->eyeX->value());}
void GLTeach::setCenterX(){ui->widget->setCenterX(ui->centerX->value());}
void GLTeach::setUpX(){ui->widget->setUpX(ui->upX->value());}

void GLTeach::setEyeY(){ui->widget->setEyeY(ui->eyeY->value());}
void GLTeach::setCenterY(){ui->widget->setCenterY(ui->centerY->value());}
void GLTeach::setUpY(){ui->widget->setUpY(ui->upY->value());}

void GLTeach::setEyeZ(){ui->widget->setEyeZ(ui->eyeZ->value());}
void GLTeach::setCenterZ(){ui->widget->setCenterZ(ui->centerZ->value());}
void GLTeach::setUpZ(){ui->widget->setUpZ(ui->upZ->value());}
void GLTeach::callScale(){ui->widget->scale(ui->scaleHSlider->value());}
void GLTeach::setMatColors()
{
    matColors.x= ui->MCRed->value()*.01;
    matColors.y= ui->MCGreen->value()*.01;
    matColors.z= ui->MCBlue->value()*.01;
    matColors.w= ui->MCAlpha->value()*.01;
    ambLC.x=ui->ALCRed->value()*.01;
    ambLC.y=ui->ALCGreen->value()*.01;
    ambLC.z=ui->ALCBlue->value()*.01;
    diffLC.x=ui->DiffRed->value()*.01;
    diffLC.y=ui->DiffGreen->value()*.01;
    diffLC.z=ui->DiffBlue->value()*.01;
    specLC.x=ui->SLCRed->value()*.01;
    specLC.y=ui->SLCGreen->value()*.01;
    specLC.z=ui->SLCBlue->value()*.01;
    shinLC.x=ui->ShinRed->value();
    shinLC.y=ui->ShinGreen->value();
    shinLC.z=ui->ShinBlue->value();
    Lpos0.x = ui->Light0X->value();
    Lpos0.y = ui->Light0Y->value();
    Lpos0.z = ui->Light0Z->value();
    Lpos1.x = ui->Light1X->value();
    Lpos1.y = ui->Light1Y->value();
    Lpos1.z = ui->Light1Z->value();

    ui->widget->setMatColor(matColors,ambLC,shinLC, diffLC,specLC,Lpos0,Lpos1);

}
void GLTeach::moveXY()
{
    translate.x = ui->moveX->value();
    translate.z = ui->MoveY->value();
    ui->widget->translate(translate.x,translate.y,translate.z);
}
