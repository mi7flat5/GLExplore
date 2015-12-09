#include "glteach.h"
#include <QApplication>
#include<glut.h>
#include<glwidget.h>
int main(int argc, char *argv[])
{
   // glutInit(&argc,argv);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    QApplication a(argc, argv);
    GLTeach w;

    w.show();


    return a.exec();
}
