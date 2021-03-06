TEMPLATE = app
VERSION = 0.1.0
QT = gui \
    core \
    xml \
    opengl
CONFIG += qt \
    warn_on \
    opengl \
    uitools \
    x11 \
    staticlib \
    app_bundle \
    release
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
BUILDDIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui
HEADERS = src/mainwindowimpl.h \
    src/formats/Mesh.h \
    build/ui_mainwindow.h \
    src/objects.h \
    src/glwidget.h
SOURCES = src/mainwindowimpl.cpp \
    src/main.cpp \
    src/formats/Mesh.cpp \
    src/objects.cpp \
    src/glwidget.cpp

win32: { 
    message(Building for Windows)
    LIBS = -L"P:\dev\Tools\Parade\Parade3D\lib" \
        -lQGLViewer2 \
        -L"C:\Program Files\NVIDIA Corporation\Cg\bin" \
        -lCg \
        -lglut32 \
        -lCgGL
    INCLUDEPATH = "C:\Program files\libQGLViewer" \
        "C:\Program Files\NVIDIA Corporation\Cg\include"
}
else { 
    message(Building for unix or mac os X)
    LIBS = -lQGLViewer \
        -lCg \
        -lCgGL
}
TARGET = parade3d-bin
RESOURCES += icons/menuicons.qrc
DISTFILES += icons/*.png \
    icons/*.svg \
    lib/*.so \
    Documentation/* \
    mayaplugin/mayaplugin.pro \
    mayaplugin/scripts/*.mel \
    mayaplugin/src/*.cpp \
    mayaplugin/src/*.h \
    TODO \
    README \
    License/gpl-3.0.txt \
    bin/parade3d
