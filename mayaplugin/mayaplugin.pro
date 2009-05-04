#-------------------------------------------------
#
# Project created by QtCreator 2009-05-04T15:11:36
#
#-------------------------------------------------

TEMPLATE = lib
VER_MAJ = 0
VER_MIN = 1
VER_PAT = 0

QMAKE_CC		= gcc-4.1
QMAKE_CXX		= g++-4.1

MAYA_LOCATION		= /home/Apps/Maya
MAYA_VERSION		= 10.0_2009
BUILD_VERSION		= linux_x86_64
PLUG_LOCATION		= /home/Apps/SharedConf/maya/$${MAYA_VERSION}/$${BUILD_VERSION}/modules/dev/plug-ins/

QMAKE_CFLAGS		= -DBits64_ -m64 -DUNIX -D_BOOL -DLINUX -DFUNCPROTO -D_GNU_SOURCE -DLINUX_64 -fPIC \
                            -fno-strict-aliasing -DREQUIRE_IOSTREAM -Wno-deprecated -O3 -Wall \
                            -Wno-multichar -Wno-comment -Wno-sign-compare -funsigned-char \
                            -Wno-reorder -fno-gnu-keywords -ftemplate-depth-25 -pthread


QMAKE_CXXFLAGS          = $${QMAKE_CFLAGS} $${WARNFLAGS} -Wno-deprecated -fno-gnu-keywords
INCLUDEPATH             = $${MAYA_LOCATION}/maya2009-x64/include \
                            -I/usr/X11R6/include
LIBS                    = -L$${MAYA_LOCATION}/maya2009-x64/lib -lFoundation -lOpenMaya -lGL -lGLU -lm 	\
                            -lMaya -lOpenMaya -lOpenMayaAnim 			\
                        -lOpenMayaUI -lOpenMayalib

TARGET = parade3d-$${MAYA_VERSION}_$${BUILD_VERSION}
DESTDIR = bin

DEFINES += PLUGIN_LIBRARY


SOURCES += src/*.cpp

HEADERS += src/*.h

DISTFILES = scripts/*.mel \
            bin/*
