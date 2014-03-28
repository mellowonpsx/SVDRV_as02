TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    code_unused.c

#INCLUDEPATH += -L/usr/lib/
LIBS += -lglut
LIBS += -lGL
LIBS += -lGLU
LIBS += -lSDL
LIBS += -lSDL_image
