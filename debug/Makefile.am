BUILDTOP=..
TOPLEVEL=${srcdir}/..
TOOLDIR=${TOPLEVEL}/tools

LIBDIR=${TOPLEVEL}/lib
INCDIR=${TOPLEVEL}/include/
UNITTEST=${TOPLEVEL}/unittests

AM_CPPFLAGS = -g -O1 -I$(TOPLEVEL)/include -I$(BUILDTOP)/include -I$(TOOLDIR) -I/usr/X11R6/include -I$(TOPLEVEL)/utils/gtest/include -DTOPDIR=\"${abs_top_srcdir}\"

bin_PROGRAMS = lviewer.debug

lviewer_debug_CPPFLAGS = -g -O1 -I$(TOPLEVEL)/include -I$(BUILDTOP)/include -I$(TOOLDIR) -I/usr/X11R6/include -I$(TOPLEVEL)/utils/gtest/include -DTOPDIR=\"${abs_top_srcdir}\"

lviewer_debug_LDFLAGS = -lglut -lGLU -lGL -L/usr/X11R6/lib/ -lXext -lX11 -L$(BUILDTOP)/utils/gtest/lib -lgtest

SRC =	${TOOLDIR}/main.cpp \
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
	${INCDIR}/framework.h \
	${LIBDIR}/framework.cpp \
	${INCDIR}/GLM/glm.h \
	${LIBDIR}/GLM/glm.cpp \
	${INCDIR}/GLM/texture.h \
	${LIBDIR}/GLM/glm_texture.cpp \
	${LIBDIR}/GLM/glmimg.cpp \
	${INCDIR}/LLib.h \
	${INCDIR}/LGlobal/LGlobal.h \
	${INCDIR}/LTranslateMatrix/LTranslateMatrix.h \
	${LIBDIR}/LTranslateMatrix.cpp \
	${INCDIR}/LViewer/LViewer.h \
	${LIBDIR}/LViewer.cpp \
	${INCDIR}/Triangle/Model.h \
	${LIBDIR}/Triangle/Model.cpp \
	${INCDIR}/Triangle/Color.h \
	${LIBDIR}/Triangle/Color.cpp \
	${INCDIR}/Triangle/Vertex.h \
	${LIBDIR}/Triangle/Vertex.cpp \
	${INCDIR}/Triangle/Material.h \
	${LIBDIR}/Triangle/Material.cpp \
	${INCDIR}/Triangle/ModelToVertex.h \
	${LIBDIR}/Triangle/ModelToVertex.cpp \
	${INCDIR}/Triangle/Line.h \
	${LIBDIR}/Triangle/Line.cpp \
	${INCDIR}/Triangle/Triangle.h \
	${LIBDIR}/Triangle/Triangle.cpp \
	${INCDIR}/Triangle/Space.h \
	${LIBDIR}/Triangle/Space.cpp \
	${INCDIR}/Triangle/Camera.h \
	${LIBDIR}/Triangle/Camera.cpp \
	${INCDIR}/Triangle/Light.h \
	${LIBDIR}/Triangle/Light.cpp \
	${INCDIR}/Triangle/DrawLine.h \
	${LIBDIR}/Triangle/DrawLine.cpp \
	${INCDIR}/Triangle/LineIterator.h \
	${LIBDIR}/Triangle/LineIterator.cpp \
	${INCDIR}/Triangle/Painter.h \
	${LIBDIR}/Triangle/Painter.cpp \
	${INCDIR}/Triangle/DrawTriangle.h \
	${LIBDIR}/Triangle/DrawTriangle.cpp \
	${INCDIR}/Triangle/TriangleIterator.h \
	${LIBDIR}/Triangle/TriangleIterator.cpp \
	${INCDIR}/Triangle/Vectors.h \
	${LIBDIR}/Triangle/Vectors.cpp \
	${INCDIR}/Triangle/Transformation.h \
	${LIBDIR}/Triangle/Transformation.cpp \
	${INCDIR}/Triangle/Projection.h \
	${LIBDIR}/Triangle/Projection.cpp \
	${INCDIR}/Triangle/FrameBuffer.h \
	${LIBDIR}/Triangle/FrameBuffer.cpp \
	${INCDIR}/Triangle/Texture.h \
	${LIBDIR}/Triangle/Texture.cpp \
	${INCDIR}/Triangle/Image.h \
	${LIBDIR}/Triangle/Image.cpp \
	${INCDIR}/Triangle/RenderEvents.h \
	${LIBDIR}/Triangle/RenderEvents.cpp \
	${INCDIR}/Triangle/BumpMap.h \
	${LIBDIR}/Triangle/BumpMap.cpp \
	${INCDIR}/Events/Stage.h \
	${LIBDIR}/Events/Stage.cpp \
	${INCDIR}/Events/Event.h \
	${LIBDIR}/Events/Event.cpp \
	${INCDIR}/Events/KeyEvent.h \
	${LIBDIR}/Events/KeyEvent.cpp \
	${INCDIR}/Events/MouseEvent.h \
	${LIBDIR}/Events/MouseEvent.cpp \
	${INCDIR}/Events/EventRegistry.h \
	${LIBDIR}/Events/EventRegistry.cpp \
	${INCDIR}/Support/ManagedStatic.h \
	${LIBDIR}/Support/ManagedStatic.cpp \
	${INCDIR}/Support/Flags.h \
	${INCDIR}/Support/FileHandle.h \
	${LIBDIR}/Support/FileHandle.cpp

TEST_SRC = ${UNITTEST}/AlgebraTest.h \
	${UNITTEST}/AlgebraTest.cpp \
	${UNITTEST}/SpaceTest.h \
	${UNITTEST}/SpaceTest.cpp \
	${UNITTEST}/ImageTest.h \
	${UNITTEST}/ImageTest.cpp \
	${UNITTEST}/LineTest.h \
	${UNITTEST}/LineTest.cpp \
	${UNITTEST}/TriangleTest.h \
	${UNITTEST}/TriangleTest.cpp \
	${UNITTEST}/ProjectTest.h \
	${UNITTEST}/ProjectTest.cpp \
	${UNITTEST}/TextureTest.h \
	${UNITTEST}/TextureTest.cpp

SOURCE = $(SRC) $(TEST_SRC)
lviewer_debug_SOURCES = $(SOURCE)
