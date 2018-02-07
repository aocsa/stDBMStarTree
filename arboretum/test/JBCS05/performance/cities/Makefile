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
SRC= app.cpp Cities.cpp city.cpp ../../../GNUPlot.cpp
OBJS=$(subst .cpp,.o,$(SRC))


# Implicit Rules
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

Cities: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o Cities $(INCLUDE) $(LIBPATH) $(LIBS)
