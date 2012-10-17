BUILDTOP=..
TOPLEVEL=${srcdir}/..
TOOLDIR=${TOPLEVEL}/tools

LIBDIR=${TOPLEVEL}/lib
INCDIR=${TOPLEVEL}/include/

AM_CPPFLAGS = -g -O1 -I$(TOPLEVEL)/include -I$(BUILDTOP)/include -I$(TOOLDIR) -I/usr/X11R6/include

bin_PROGRAMS = lviewer.debug

lviewer_debug_CPPFLAGS = -g -O1 -I$(TOPLEVEL)/include -I$(BUILDTOP)/include -I$(TOOLDIR) -I/usr/X11R6/include

lviewer_debug_LDFLAGS = -L$(BUILDTOP)/lib -lglut -lGLU -lGL -L/usr/X11R6/lib/ -lXmu -lXi -lXext -lX11 -lXt

lviewer_debug_SOURCES = ${TOOLDIR}/main.cpp \
	${TOOLDIR}/stdafx.h \
	${INCDIR}/algebra3/algebra3.h \
	${LIBDIR}/algebra3.cpp \
	${INCDIR}/framework.h \
	${LIBDIR}/framework.cpp \
	${INCDIR}/GLM/glm.h \
	${LIBDIR}/glm.cpp \
	${INCDIR}/GLM/texture.h \
	${LIBDIR}/texture.cpp \
	${LIBDIR}/glmimg.cpp \
	${INCDIR}/LLib.h \
	${INCDIR}/LGlobal/LGlobal.h \
	${INCDIR}/LTranslateMatrix/LTranslateMatrix.h \
	${LIBDIR}/LTranslateMatrix.cpp \
	${INCDIR}/LViewer/LViewer.h \
	${LIBDIR}/LViewer.cpp \
	${INCDIR}/Support/Flags.h \
	${INCDIR}/Support/FileHandle.h \
	${LIBDIR}/FileHandle.cpp

