#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T23:18:11
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLTeach
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        glteach.cpp \
    glwidget.cpp

HEADERS  += glteach.h \
    glwidget.h \
    glm-0.9.2.7/glm/glm.hpp

FORMS    += glteach.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../GLEW/glew-1.13.0/lib/Release/x64/ -lglew32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../GLEW/glew-1.13.0/lib/Release/x64/ -lglew32
else:unix: LIBS += -L$$PWD/../../../../GLEW/glew-1.13.0/lib/Release/x64/ -lglew32

INCLUDEPATH += $$PWD/../../../../GLEW/glew-1.13.0/lib/Release/x64
DEPENDPATH += $$PWD/../../../../GLEW/glew-1.13.0/lib/Release/x64

unix|win32: LIBS += -L$$PWD/../../../../GLUT/ -lglut32

INCLUDEPATH += $$PWD/../../../../GLUT
DEPENDPATH += $$PWD/../../../../GLUT

LIBS += -lopengl32
