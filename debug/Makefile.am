BUILDTOP=..
TOPLEVEL=${srcdir}/..
TOOLDIR=${TOPLEVEL}/tools

LIBDIR=${TOPLEVEL}/lib
INCDIR=${TOPLEVEL}/include/

AM_CPPFLAGS = -g -O1 -I$(TOPLEVEL)/include -I$(BUILDTOP)/include -I$(TOOLDIR) -I/usr/X11R6/include

bin_PROGRAMS = lviewer.debug

lviewer_debug_CPPFLAGS = -g -O1 -I$(TOPLEVEL)/include -I$(BUILDTOP)/include -I$(TOOLDIR) -I/usr/X11R6/include

lviewer_debug_LDFLAGS = -L$(BUILDTOP)/lib -lglut -lGLU -lGL -L/usr/X11R6/lib/ -lXext -lX11

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
	${INCDIR}/Triangle/Model.h \
	${INCDIR}/Triangle/Color.h \
	${LIBDIR}/Color.cpp \
	${INCDIR}/Triangle/Coord.h \
	${INCDIR}/Triangle/Vertex.h \
	${LIBDIR}/Vertex.cpp \
	${INCDIR}/Triangle/Line.h \
	${LIBDIR}/Line.cpp \
	${INCDIR}/Triangle/Triangle.h \
	${LIBDIR}/Triangle.cpp \
	${INCDIR}/Triangle/Space.h \
	${LIBDIR}/Space.cpp \
	${INCDIR}/Triangle/DrawLine.h \
	${LIBDIR}/DrawLine.cpp \
	${INCDIR}/Triangle/LineIterator.h \
	${LIBDIR}/LineIterator.cpp \
	${INCDIR}/Triangle/Painter.h \
	${LIBDIR}/Painter.cpp \
	${LIBDIR}/Model.cpp \
	${INCDIR}/Triangle/FrameBuffer.h \
	${LIBDIR}/FrameBuffer.cpp \
	${INCDIR}/Support/Flags.h \
	${INCDIR}/Support/FileHandle.h \
	${LIBDIR}/FileHandle.cpp

