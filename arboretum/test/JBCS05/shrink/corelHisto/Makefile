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
SRC= app.cpp corelHisto.cpp ../../../GNUPlot.cpp
OBJS=$(subst .cpp,.o,$(SRC))


# Implicit Rules
%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

corelHisto: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o corelHisto $(INCLUDE) $(LIBPATH) $(LIBS)
