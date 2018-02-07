# Makefile for GCC
#
# Author: Marcos Rodrigues Vieira
#
CC=gcc
CFLAGS=
INCLUDEPATH=../../../../include
LIBPATH=-L../../../../lib
INCLUDE=-I$(INCLUDEPATH)
LIBS=-lstdc++ -lm -larboretum
SRC= app.cpp Vector.cpp ../../../GNUPlot.cpp ../../../../src/stLevelDiskAccess.cpp
OBJS=$(subst .cpp,.o,$(SRC))


# Implicit Rules
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

Vector: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o Vector $(INCLUDE) $(LIBPATH) $(LIBS)
