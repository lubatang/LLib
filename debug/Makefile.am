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
	${INCDIR}/algebra/vec2.h \
	${LIBDIR}/algebra/vec2.cpp \
	${INCDIR}/algebra/vec3.h \
	${LIBDIR}/algebra/vec3.cpp \
	${INCDIR}/algebra/vec4.h \
	${LIBDIR}/algebra/vec4.cpp \
	${INCDIR}/algebra/mat3.h \
	${LIBDIR}/algebra/mat3.cpp \
	${INCDIR}/algebra/mat4.h \
	${LIBDIR}/algebra/mat4.cpp \
	${INCDIR}/algebra/algebra.h \
	${LIBDIR}/algebra/algebra.cpp \
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
	${INCDIR}/Triangle/ColorIterator.h \
	${LIBDIR}/ColorIterator.cpp \
	${INCDIR}/Triangle/Coord.h \
	${INCDIR}/Triangle/Vertex.h \
	${INCDIR}/Triangle/GenVertex.h \
	${LIBDIR}/GenVertex.cpp \
	${INCDIR}/Triangle/ModelVertex.h \
	${LIBDIR}/ModelVertex.cpp \
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
	${INCDIR}/Triangle/DrawTriangle.h \
	${LIBDIR}/DrawTriangle.cpp \
	${INCDIR}/Triangle/TriangleIterator.h \
	${LIBDIR}/TriangleIterator.cpp \
	${LIBDIR}/Painter.cpp \
	${LIBDIR}/Model.cpp \
	${INCDIR}/Triangle/FrameBuffer.h \
	${LIBDIR}/FrameBuffer.cpp \
	${INCDIR}/Support/Flags.h \
	${INCDIR}/Support/FileHandle.h \
	${LIBDIR}/FileHandle.cpp

